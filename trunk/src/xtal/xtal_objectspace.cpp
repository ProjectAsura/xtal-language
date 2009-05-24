#include "xtal.h"
#include "xtal_macro.h"

#include "xtal_objectspace.h"

#ifdef XTAL_DEBUG_PRINT
#include <map>
#include <string>
#endif

namespace xtal{

enum{
	OBJECTS_ALLOCATE_SHIFT = 8,
	OBJECTS_ALLOCATE_SIZE = 1 << OBJECTS_ALLOCATE_SHIFT,
	OBJECTS_ALLOCATE_MASK = OBJECTS_ALLOCATE_SIZE-1
};

struct ScopeCounter{
	uint_t* p;
	ScopeCounter(uint_t* p):p(p){ *p+=1; }
	~ScopeCounter(){ *p-=1; }
};

struct ConnectedPointer{
	int_t pos;
	RefCountingBase**** bp;

	typedef std::random_access_iterator_tag iterator_category;

	typedef std::random_access_iterator_tag iterator_category;
	typedef RefCountingBase* value_type;
	typedef int_t difference_type;
	typedef int_t distance_type;	// retained
	typedef RefCountingBase** pointer;
	typedef RefCountingBase*& reference;

	ConnectedPointer()
		:pos(0), bp(0){}

	ConnectedPointer(int_t p, RefCountingBase***& pp)
		:pos(p), bp(&pp){}

	RefCountingBase*& operator *(){
		return (*bp)[pos>>OBJECTS_ALLOCATE_SHIFT][pos&OBJECTS_ALLOCATE_MASK];
	}

	ConnectedPointer& operator ++(){
		++pos;
		return *this;
	}

	ConnectedPointer operator ++(int){
		ConnectedPointer temp(pos, *bp);
		++pos;
		return temp; 
	}

	ConnectedPointer& operator --(){
		--pos;
		return *this;
	}

	ConnectedPointer operator --(int){
		ConnectedPointer temp(pos, *bp);
		--pos;
		return temp; 
	}

	friend bool operator==(const ConnectedPointer& a, const ConnectedPointer& b){
		XTAL_ASSERT(a.bp==b.bp);
		return a.pos==b.pos;
	}

	friend bool operator!=(const ConnectedPointer& a, const ConnectedPointer& b){
		XTAL_ASSERT(a.bp==b.bp);
		return a.pos!=b.pos;
	}

	friend bool operator<(const ConnectedPointer& a, const ConnectedPointer& b){
		XTAL_ASSERT(a.bp==b.bp);
		return a.pos<b.pos;
	}

	friend bool operator>(const ConnectedPointer& a, const ConnectedPointer& b){
		XTAL_ASSERT(a.bp==b.bp);
		return a.pos>b.pos;
	}

	friend bool operator<=(const ConnectedPointer& a, const ConnectedPointer& b){
		XTAL_ASSERT(a.bp==b.bp);
		return a.pos<=b.pos;
	}

	friend bool operator>=(const ConnectedPointer& a, const ConnectedPointer& b){
		XTAL_ASSERT(a.bp==b.bp);
		return a.pos>=b.pos;
	}

	friend int_t operator-(const ConnectedPointer& a, const ConnectedPointer& b){
		XTAL_ASSERT(a.bp==b.bp);
		return a.pos - b.pos;
	}

	friend ConnectedPointer operator-(const ConnectedPointer& a, int_t b){
		return ConnectedPointer(a.pos - b, *a.bp);
	}

	friend ConnectedPointer operator-(int_t a, const ConnectedPointer& b){
		return ConnectedPointer(a - b.pos, *b.bp);
	}

	friend ConnectedPointer operator+(const ConnectedPointer& a, int_t b){
		return ConnectedPointer(a.pos + b, *a.bp);
	}

	friend ConnectedPointer operator+(int_t a, const ConnectedPointer& b){
		return ConnectedPointer(a + b.pos, *b.bp);
	}
};


void xtal::ObjectSpace::print_alive_objects(){
#ifdef XTAL_DEBUG_PRINT

	ConnectedPointer current(objects_count_, objects_list_begin_);
	ConnectedPointer begin(0, objects_list_begin_);

	std::map<std::string, int> table;
	for(ConnectedPointer it = begin; it!=current; ++it){
		switch(type(**it)){
		XTAL_DEFAULT;
		XTAL_CASE(TYPE_BASE){ table["Base"]++; }
		XTAL_CASE(TYPE_STRING){ unchecked_ptr_cast<String>(ap(**it))->is_interned() ? table["iString"]++ : table["String"]++; /*table[unchecked_ptr_cast<String>(ap(**it))->c_str()]++;*/ }
		XTAL_CASE(TYPE_ARRAY){ table["Array"]++; }
		XTAL_CASE(TYPE_VALUES){ table["Values"]++; }
		XTAL_CASE(TYPE_TREE_NODE){ table["xpeg::TreeNode"]++; }
		XTAL_CASE(TYPE_NATIVE_METHOD){ table["NativeMethod"]++; }
		XTAL_CASE(TYPE_NATIVE_FUN){ table["NativeFun"]++; }
		}
	}

	std::map<std::string, int>::iterator it=table.begin(), last=table.end();
	for(; it!=last; ++it){
		printf("alive %s %d\n", it->first.c_str(), it->second);
	}
	int m = (objects_list_end_ - objects_list_begin_)*OBJECTS_ALLOCATE_SIZE;
	printf("m %d\n", m);

	//printf("used_memory %d\n", used_memory);
#endif
}

void ObjectSpace::initialize(){
	objects_list_begin_ = 0;
	objects_list_current_ = 0;
	objects_list_end_ = 0;
	gcobservers_begin_ = 0;
	gcobservers_current_ = 0;
	gcobservers_end_ = 0;
	objects_count_ = 0;
	objects_count_limit_ = 0;
	cycle_count_ = 0;

	disable_finalizer_ = false;

	disable_gc();

	expand_objects_list();
	objects_begin_ = objects_current_ = *objects_list_current_++;
	objects_end_ = objects_begin_+OBJECTS_ALLOCATE_SIZE;

	static CppClassSymbolData key;
	class_table_.resize(key.value);
	for(uint_t i=0; i<key.value; ++i){
		class_table_[i] = 0;
	}

	CppClassSymbolData* symbols[] = { 
		CppClassSymbol<void>::value,
		CppClassSymbol<Any>::value,
		CppClassSymbol<Class>::value,
		CppClassSymbol<Array>::value,
		CppClassSymbol<String>::value,
	};

	uint_t nsize = sizeof(symbols)/sizeof(symbols[0]);

	for(uint_t i=0; i<nsize; ++i){
		class_table_[symbols[i]->value] = (Class*)Base::operator new(sizeof(Class));
	}

	for(uint_t i=0; i<nsize; ++i){
		Base* p = class_table_[symbols[i]->value];
		new(p) Base();
	}
		
	for(uint_t i=0; i<nsize; ++i){
		Base* p = class_table_[symbols[i]->value];
		new(p) Class(Class::cpp_class_t());
	}

	for(uint_t i=0; i<nsize; ++i){
		Base* p = class_table_[symbols[i]->value];
		p->set_class(xtal::cpp_class<Class>());
	}
	
	for(uint_t i=0; i<nsize; ++i){
		Base* p = class_table_[symbols[i]->value];
		register_gc(p);
	}

	//////////////////////////////////////////////////

	for(uint_t i=0; i<class_table_.size(); ++i){
		if(!class_table_[i]){
			class_table_[i] = xnew<Class>(Class::cpp_class_t()).get();
			class_table_[i]->inc_ref_count();
		}
	}

	CppClassSymbolData* prev = key.prev;
	for(uint_t i=class_table_.size(); i>1; --i){
		class_table_[i-1]->set_symbol_data(prev);
		prev = prev->prev;
	}

	//////////////////////////////////////////////////

	{
		static CppVarSymbolData key(0);
		var_table_ = xnew<Array>(key.value);
		CppVarSymbolData* prev = key.prev;
		for(uint_t i=var_table_->size(); i>1; --i){
			var_table_->set_at(i-1, prev->maker ? prev->maker() : null);
			prev = prev->prev;
		}
	}
}

void ObjectSpace::uninitialize(){
	for(uint_t i=0; i<class_table_.size(); ++i){
		if(class_table_[i]){
			class_table_[i]->dec_ref_count();
			class_table_[i] = 0;
		}
	}

	for(uint_t i=0; i<var_table_->size(); ++i){
		var_table_->set_at(i, undefined);
	}
	var_table_ = null;

	class_table_.release();
	clear_cache();

	disable_finalizer_ = true;

	full_gc();

	if(objects_count_ != 0){
		if(!ignore_memory_assert()){
			//fprintf(stderr, "finished gc\n");
			//fprintf(stderr, "exists cycled objects %d\n", objects_count_);
			print_alive_objects();

			// ����assert�łƂ܂�ꍇ�A�I�u�W�F�N�g�����ׂĊJ���ł��Ă��Ȃ��B
			// �O���[�o���ϐ��ȂǂŃI�u�W�F�N�g�������Ă��Ȃ����A�z�Q�Ƃ͂Ȃ������ׂ邱�ƁB
			XTAL_ASSERT(false);
		}

		// �����I�ɊJ�����Ă��܂���
		{
			ConnectedPointer current(objects_count_, objects_list_begin_);
			ConnectedPointer begin(0, objects_list_begin_);

			destroy_objects(begin, current);
			free_objects(begin, current);
		}

	}

	for(RefCountingBase*** it=objects_list_begin_; it!=objects_list_end_; ++it){
		RefCountingBase** begin = *it;
		RefCountingBase** current = *it;
		RefCountingBase** end = *it+OBJECTS_ALLOCATE_SIZE;
		fit_simple_dynamic_pointer_array(&begin, &end, &current);
	}

	objects_list_current_ = objects_list_begin_;

	fit_simple_dynamic_pointer_array(&gcobservers_begin_, &gcobservers_end_, &gcobservers_current_);
	fit_simple_dynamic_pointer_array(&objects_list_begin_, &objects_list_end_, &objects_list_current_);

}

void ObjectSpace::enable_gc(){
	cycle_count_--;
}

void ObjectSpace::disable_gc(){
	cycle_count_++;
}
	
void ObjectSpace::expand_objects_list(){
	if(objects_list_current_==objects_list_end_){
		expand_simple_dynamic_pointer_array(&objects_list_begin_, &objects_list_end_, &objects_list_current_, 1);
		for(RefCountingBase*** it=objects_list_current_; it!=objects_list_end_; ++it){
			RefCountingBase** begin = 0;
			RefCountingBase** current = 0;
			RefCountingBase** end = 0;
			expand_simple_dynamic_pointer_array(&begin, &end, &current, OBJECTS_ALLOCATE_SIZE);
			*it = begin;
		}
	}
}

uint_t ObjectSpace::alive_object_count(){
	return (objects_list_current_ - objects_list_begin_ - 1)*OBJECTS_ALLOCATE_SIZE + (objects_current_ - objects_begin_);
}

RefCountingBase* ObjectSpace::alive_object(uint_t i){
	ConnectedPointer current(i, objects_list_begin_);
	return *current;
}

void ObjectSpace::before_gc(){
	for(GCObserver** it = gcobservers_begin_; it!=gcobservers_current_; ++it){
		(*it)->before_gc();
	}
}

void ObjectSpace::after_gc(){
	for(GCObserver** it = gcobservers_begin_; it!=gcobservers_current_; ++it){
		(*it)->after_gc();
	}
}

uint_t ObjectSpace::swap_dead_objects(ConnectedPointer& alive, ConnectedPointer current){
	uint_t num = 0;
	for(ConnectedPointer it=alive; it!=current;){
		if((*it)->ungc()==0){
			--current;
			++num;
			RefCountingBase* temp = *it;
			*it = *current;
			*current = temp;
		}
		else{
			++it;
		}
	}
	alive = current;
	return num;
}

void ObjectSpace::destroy_objects(ConnectedPointer it, ConnectedPointer current){
	for(; it!=current; ++it){
		(*it)->destroy();
	}
}

void ObjectSpace::free_objects(ConnectedPointer it, ConnectedPointer current){
	for(; it!=current; ++it){
		(*it)->object_free();
	}
}

void ObjectSpace::adjust_objects_list(ConnectedPointer it){
	objects_count_ = it.pos;
	objects_list_current_ = objects_list_begin_ + (objects_count_>>OBJECTS_ALLOCATE_SHIFT);
	expand_objects_list();
	objects_begin_ = *objects_list_current_++;
	objects_current_ = objects_begin_ + (objects_count_&OBJECTS_ALLOCATE_MASK);
	objects_end_ = objects_begin_ + OBJECTS_ALLOCATE_SIZE;
	XTAL_ASSERT(objects_list_current_<=objects_list_end_);

	objects_count_limit_ = objects_count_limit_*30/50 + objects_count_*15/50;
}

namespace{
	struct RefCountComp{
		bool operator()(RefCountingBase* a, RefCountingBase* b){
			if(a->ref_count()>b->ref_count()){
				return true;
			}
			if(a->ref_count()<b->ref_count()){
				return false;
			}
			return a->gene_count() > b->gene_count();
		}
	};
}

void ObjectSpace::sort_objects(){
	ConnectedPointer begin(0, objects_list_begin_);
	ConnectedPointer end(objects_count_, objects_list_begin_);

	std::sort(begin, end, RefCountComp());

	for(ConnectedPointer it=begin; it!=end; ++it){
		(*it)->inc_gene_count();
	}
}

void ObjectSpace::add_ref_count_objects(ConnectedPointer it, ConnectedPointer current, int_t v){
	Visitor m(v);
	for(; it!=current; ++it){
		(*it)->visit_members(m);
	}
}


void ObjectSpace::gc(){
	if(cycle_count_!=0){ return; }

	ScopeCounter cc(&cycle_count_);

	if(objects_count_limit_>=objects_count_){
		objects_count_limit_ = objects_count_;
		return;
	}
	
	ConnectedPointer current(objects_count_, objects_list_begin_);
	ConnectedPointer begin(objects_count_limit_, objects_list_begin_);
	ConnectedPointer alive = begin;

	before_gc();

	ConnectedPointer dead = current;
	for(int_t i=0; i<3; ++i){
		if(swap_dead_objects(alive, dead)==0){
			break;
		}

		if(i>=1){
			i = i;
		}

		add_ref_count_objects(alive, dead, -1);

		dead = alive;
		alive = begin;
	}
	
	add_ref_count_objects(dead, current, 1);

	after_gc();
	destroy_objects(dead, current);
	free_objects(dead, current);
	adjust_objects_list(dead);
}

void ObjectSpace::full_gc(){
	if(cycle_count_!=0){ return; }
	{
		ScopeCounter cc(&cycle_count_);
				
		while(true){			
			ConnectedPointer current(objects_count_, objects_list_begin_);
			ConnectedPointer begin(0, objects_list_begin_);
			if(current==begin){
				break;
			}

			before_gc();

			// �Q�ƃJ�E���^�����炷
			// ����ɂ��A���[�g���玦����Ă���ȊO�̃I�u�W�F�N�g�͎Q�ƃJ�E���^��0�ƂȂ�
			add_ref_count_objects(begin, current, -1);
		
			ConnectedPointer alive = begin;

			{ // �����҂�������
				// �����҂Ǝ���Ȃ��ł�l�������҂Ƃ����ӂ��Ɋ֌W��􂢏o��

				Visitor m(1);
				bool end = false;
				while(!end){
					end = true;
					for(ConnectedPointer it = alive; it!=current; ++it){
						if((*it)->ref_count()!=0){
							end = false;
							(*it)->visit_members(m); // �����m��I�u�W�F�N�g�́A�Q�ƃJ�E���^�����ɖ߂�
							std::swap(*it, *alive++);
						}
					}
				}
			}

			// begin �` alive�܂ł̃I�u�W�F�N�g�͐����m��
			// alive �` current�܂ł̃I�u�W�F�N�g�͎��S�\��


			// ���҂��A�Q�ƃJ�E���^�����ɖ߂�
			add_ref_count_objects(alive, current, 1);

			after_gc();

			if(!disable_finalizer_){
				bool exists_have_finalizer = false;
				// ���҂�finalizer�𑖂点��
				for(ConnectedPointer it = alive; it!=current; ++it){
					if((*it)->have_finalizer()){
						exists_have_finalizer = true;
						((Base*)(*it))->finalize();
					}
				}

				if(exists_have_finalizer){
					// finalizer�ŃI�u�W�F�N�g�����ꂽ��������Ȃ��̂ŁAcurrent�𔽉f����
					current = ConnectedPointer(objects_count_, objects_list_begin_);
					begin = ConnectedPointer(0, objects_list_begin_);

					// ���҂������Ԃ��������m��Ȃ��̂Ń`�F�b�N����

					before_gc();

					// �Q�ƃJ�E���^�����炷
					add_ref_count_objects(alive, current, -1);
					
					{ // ���҂̒����畜�������҂�������
						Visitor m(1);
						bool end = false;
						while(!end){
							end = true;
							for(ConnectedPointer it = alive; it!=current; ++it){
								if((*it)->ref_count()!=0){
									end = false;
									(*it)->visit_members(m); // �����m��I�u�W�F�N�g�́A�Q�ƃJ�E���^�����ɖ߂�
									std::swap(*it, *alive++);
								}
							}
						}
					}

					// begin �` alive�܂ł̃I�u�W�F�N�g�͐����m��
					// alive �` current�܂ł̃I�u�W�F�N�g�͎��S�m��

					// ���҂��A�Q�ƃJ�E���^�����ɖ߂�
					add_ref_count_objects(alive, current, 1);

					after_gc();
				}
			}

			destroy_objects(alive, current);
			free_objects(alive, current);
			
			adjust_objects_list(alive);

			if(current==alive){
				break;
			}

			current = alive;
		}

		/*{
			ConnectedPointer current(objects_count_, objects_list_begin_);
			ConnectedPointer begin(0, objects_list_begin_);

			for(ConnectedPointer it = begin; it!=current; ++it){
				if(typeid(**it)==typeid(Code))
				printf("alive %s\n", typeid(**it).name());
			}
		}*/

		for(RefCountingBase*** it=objects_list_current_; it!=objects_list_end_; ++it){
			RefCountingBase** begin = *it;
			RefCountingBase** current = *it;
			RefCountingBase** end = *it+OBJECTS_ALLOCATE_SIZE;
			fit_simple_dynamic_pointer_array(&begin, &end, &current);
		}
		fit_simple_dynamic_pointer_array(&objects_list_begin_, &objects_list_end_, &objects_list_current_);

		sort_objects();
	}
}

void ObjectSpace::register_gc(RefCountingBase* p){
	p->inc_ref_count();

	if(objects_current_==objects_end_){
		ScopeCounter cc(&cycle_count_);

		expand_objects_list();
		objects_begin_ = objects_current_ = *objects_list_current_++;
		objects_end_ = objects_begin_+OBJECTS_ALLOCATE_SIZE;
	}

	*objects_current_++ = p;
	objects_count_++;
}

void ObjectSpace::register_gc_observer(GCObserver* p){
	if(gcobservers_current_==gcobservers_end_){
		expand_simple_dynamic_pointer_array(&gcobservers_begin_, &gcobservers_end_, &gcobservers_current_, 64);
	}
	*gcobservers_current_++ = p;
}

void ObjectSpace::unregister_gc_observer(GCObserver* p){
	for(GCObserver** it = gcobservers_begin_; it!=gcobservers_current_; ++it){
		if(*it==p){
			std::swap(*it, *--gcobservers_current_);
			break;
		}
	}
}

void ObjectSpace::bind_all(){
	for(uint_t i=0; i<class_table_.size(); ++i){
		if(class_table_[i]){
			class_table_[i]->bind();
		}
	}
}

}
