#include "xtal.h"
#include "xtal_macro.h"

#include "xtal_objectspace.h"

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
};


void ObjectSpace::initialize(){
	objects_list_begin_ = 0;
	objects_list_current_ = 0;
	objects_list_end_ = 0;
	gcobservers_begin_ = 0;
	gcobservers_current_ = 0;
	gcobservers_end_ = 0;
	objects_count_ = 0;
	prev_objects_count_ = 0;
	cycle_count_ = 0;

	disable_gc();

	expand_objects_list();
	objects_begin_ = objects_current_ = *objects_list_current_++;
	objects_end_ = objects_begin_+OBJECTS_ALLOCATE_SIZE;

	CppClassSymbolData* symbols[] = { 
		&CppClassSymbol<void>::value,
		&CppClassSymbol<Any>::value,
		&CppClassSymbol<Class>::value,
		&CppClassSymbol<CppClass>::value,
		&CppClassSymbol<Array>::value,
	};

	uint_t nsize = sizeof(symbols)/sizeof(symbols[0]);
	uint_t table[sizeof(symbols)/sizeof(symbols[0])];

	for(uint_t i=0; i<nsize; ++i){
		table[i] = register_cpp_class(symbols[i]);
	}

	for(uint_t i=0; i<nsize; ++i){
		class_table_[table[i]] = (Class*)Base::operator new(sizeof(CppClass));
	}

	for(uint_t i=0; i<nsize; ++i){
		Base* p = class_table_[table[i]];
		new(p) Base();
	}
		
	for(uint_t i=0; i<nsize; ++i){
		Base* p = class_table_[table[i]];
		new(p) CppClass();
	}

	for(uint_t i=0; i<nsize; ++i){
		Base* p = class_table_[table[i]];
		p->set_class(xtal::cpp_class<CppClass>());
	}
	
	for(uint_t i=0; i<nsize; ++i){
		Base* p = class_table_[table[i]];
		register_gc(p);
	}
}

void ObjectSpace::uninitialize(){
	for(uint_t i=0; i<class_table_.size(); ++i){
		if(class_table_[i]){
			class_table_[i]->dec_ref_count();
			class_table_[i] = 0;
		}
	}

	class_table_.release();
	full_gc();
	
	int n = (objects_list_current_ - objects_list_begin_ - 1)*OBJECTS_ALLOCATE_SIZE + (objects_current_ - objects_begin_);
	if(n != 0){
		//fprintf(stderr, "finished gc\n");
		//fprintf(stderr, " alive object = %d\n", objects_current_-objects_begin_);
		//print_alive_objects();

		for(int i=0; i<n; ++i){
			RefCountingBase* p = objects_begin_[i];
			Base* pp = (Base*)p;
			uint_t count = p->ref_count();
			count = count;
		}

		//XTAL_ASSERT(false); // �S���J���ł��ĂȂ�
	}

	for(RefCountingBase*** it=objects_list_begin_; it!=objects_list_end_; ++it){
		RefCountingBase** begin = *it;
		RefCountingBase** current = *it;
		RefCountingBase** end = *it+OBJECTS_ALLOCATE_SIZE;
		fit_simple_dynamic_pointer_array((void**&)begin, (void**&)end, (void**&)current);
	}

	objects_list_current_ = objects_list_begin_;

	fit_simple_dynamic_pointer_array((void**&)gcobservers_begin_, (void**&)gcobservers_end_, (void**&)gcobservers_current_);
	fit_simple_dynamic_pointer_array((void**&)objects_list_begin_, (void**&)objects_list_end_, (void**&)objects_list_current_);

}

const ClassPtr& ObjectSpace::new_cpp_class(const StringPtr& name, CppClassSymbolData* key){
	int_t index = register_cpp_class(key);

	if(Class* p = class_table_[index]){
		return from_this(p);
	}

	class_table_[index] = xnew<CppClass>(name).get();
	class_table_[index]->inc_ref_count();
	return from_this(class_table_[index]);
}

void ObjectSpace::enable_gc(){
	cycle_count_++;
}

void ObjectSpace::disable_gc(){
	cycle_count_--;
}
	
void ObjectSpace::expand_objects_list(){
	if(objects_list_current_==objects_list_end_){
		expand_simple_dynamic_pointer_array((void**&)objects_list_begin_, (void**&)objects_list_end_, (void**&)objects_list_current_, 4);
		for(RefCountingBase*** it=objects_list_current_; it!=objects_list_end_; ++it){
			RefCountingBase** begin = 0;
			RefCountingBase** current = 0;
			RefCountingBase** end = 0;
			expand_simple_dynamic_pointer_array((void**&)begin, (void**&)end, (void**&)current, OBJECTS_ALLOCATE_SIZE);
			*it = begin;
		}
	}
}

void print_alive_objects(){
#if XTAL_DEBUG_ALLOC!=0
/*	full_gc();

	ConnectedPointer current(objects_count_, objects_list_begin_);
	ConnectedPointer begin(0, objects_list_begin_);

	std::map<std::string, int> table;
	for(ConnectedPointer it = begin; it!=current; ++it){
		switch(type(**it)){
		XTAL_DEFAULT;
//		XTAL_CASE(TYPE_BASE){ table[typeid(*pvalue(**it)).name()]++; }
		XTAL_CASE(TYPE_STRING){ unchecked_ptr_cast<String>(ap(**it))->is_interned() ? table["iString"]++ : table["String"]++; }
		XTAL_CASE(TYPE_ARRAY){ table["Array"]++; }
		XTAL_CASE(TYPE_MULTI_VALUE){ table["MultiValue"]++; }
		XTAL_CASE(TYPE_TREE_NODE){ table["xpeg::TreeNode"]++; }
		XTAL_CASE(TYPE_NATIVE_FUN){ table["NativeFun"]++; }
		XTAL_CASE(TYPE_NATIVE_FUN_BINDED_THIS){ table["NativeFunBindedThis"]++; }
		}
	}

	std::map<std::string, int>::iterator it=table.begin(), last=table.end();
	for(; it!=last; ++it){
		printf("alive %s %d\n", it->first.c_str(), it->second);
	}

	printf("used_memory %d\n", used_memory);
*/
#endif
}

void ObjectSpace::gc(){
	if(cycle_count_!=0){ return; }
	if(stop_the_world()){
		ScopeCounter cc(&cycle_count_);
		
		ConnectedPointer current(objects_count_, objects_list_begin_);
		ConnectedPointer begin(prev_objects_count_>objects_count_ ? objects_count_ : (prev_objects_count_-prev_objects_count_/4), objects_list_begin_);
		if(current==begin){
			restart_the_world();
			return;
		}

		for(GCObserver** it = gcobservers_begin_; it!=gcobservers_current_; ++it){
			(*it)->before_gc();
		}

		ConnectedPointer alive = begin;

		for(ConnectedPointer it = alive; it!=current; ++it){
			if((*it)->ref_count()!=0 || (*it)->have_finalizer()){
				std::swap(*it, *alive++);
			}
		}

		for(GCObserver** it = gcobservers_begin_; it!=gcobservers_current_; ++it){
			(*it)->after_gc();
		}

		for(ConnectedPointer it = alive; it!=current; ++it){
			(*it)->destroy();
		}

		for(ConnectedPointer it = alive; it!=current; ++it){
			XTAL_ASSERT((*it)->ref_count()==0);
			(*it)->object_free();
			*it = 0;
		}

		{
			prev_objects_count_ = objects_count_ = alive.pos;
			objects_list_current_ = objects_list_begin_ + (objects_count_>>OBJECTS_ALLOCATE_SHIFT);
			expand_objects_list();
			objects_begin_ = *objects_list_current_++;
			objects_current_ = objects_begin_ + (objects_count_&OBJECTS_ALLOCATE_MASK);
			objects_end_ = objects_begin_ + OBJECTS_ALLOCATE_SIZE;
			XTAL_ASSERT(objects_list_current_<=objects_list_end_);
		}

		restart_the_world();
	}
}

void ObjectSpace::full_gc(){
	if(cycle_count_!=0){ return; }
	if(stop_the_world()){
		ScopeCounter cc(&cycle_count_);
		//printf("used memory %dKB\n", used_memory/1024);
				
		while(true){			
			//member_cache_table_.clear();
			//is_cache_table_.clear();

			ConnectedPointer current(objects_count_, objects_list_begin_);
			ConnectedPointer begin(0, objects_list_begin_);
			if(current==begin){
				break;
			}

			for(GCObserver** it = gcobservers_begin_; it!=gcobservers_current_; ++it){
				(*it)->before_gc();
			}

			//if(string_space_){
			//	string_space_->gc();
			//}

			{ // �Q�ƃJ�E���^�����炷
				Visitor m(-1);	
				for(ConnectedPointer it = begin; it!=current; ++it){
					(*it)->visit_members(m);
				}

				// ����ɂ��A���[�g���玦����Ă���ȊO�̃I�u�W�F�N�g�͎Q�ƃJ�E���^��0�ƂȂ�
			}
		
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


			{// ���҂��A�Q�ƃJ�E���^�����ɖ߂�
				Visitor m(1);
				for(ConnectedPointer it = alive; it!=current; ++it){
					(*it)->visit_members(m);
				}
			}

			for(GCObserver** it = gcobservers_begin_; it!=gcobservers_current_; ++it){
				(*it)->after_gc();
			}

			{
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

					for(GCObserver** it = gcobservers_begin_; it!=gcobservers_current_; ++it){
						(*it)->before_gc();
					}

					{ // �Q�ƃJ�E���^�����炷
						Visitor m(-1);	
						for(ConnectedPointer it = alive; it!=current; ++it){
							(*it)->visit_members(m);
						}
					}
					
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


					{// ���҂��A�Q�ƃJ�E���^�����ɖ߂�
						Visitor m(1);
						for(ConnectedPointer it = alive; it!=current; ++it){
							(*it)->visit_members(m);
						}
					}

					for(GCObserver** it = gcobservers_begin_; it!=gcobservers_current_; ++it){
						(*it)->after_gc();
					}
				}
			}

			for(ConnectedPointer it = alive; it!=current; ++it){
				//printf("delete %s\n", typeid(**it).name());
				(*it)->destroy();
			}

			for(ConnectedPointer it = alive; it!=current; ++it){
				XTAL_ASSERT((*it)->ref_count()==0);
				(*it)->object_free();
				*it = 0;
			}
			
			{
				prev_objects_count_ = objects_count_ = alive.pos;
				objects_list_current_ = objects_list_begin_ + (objects_count_>>OBJECTS_ALLOCATE_SHIFT);
				expand_objects_list();
				objects_begin_ = *objects_list_current_++;
				objects_current_ = objects_begin_ + (objects_count_&OBJECTS_ALLOCATE_MASK);
				objects_end_ = objects_begin_ + OBJECTS_ALLOCATE_SIZE;
				XTAL_ASSERT(objects_list_current_<=objects_list_end_);
			}

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

//		printf("used memory %dKB\n", used_memory/1024);
		restart_the_world();
	}
}

void ObjectSpace::register_gc(RefCountingBase* p){
	p->inc_ref_count();

	if(objects_current_==objects_end_){
		ScopeCounter cc(&cycle_count_);
		//gc();
		expand_objects_list();
		objects_begin_ = objects_current_ = *objects_list_current_++;
		objects_end_ = objects_begin_+OBJECTS_ALLOCATE_SIZE;
	}

	*objects_current_++ = p;
	objects_count_++;
}

void ObjectSpace::register_gc_observer(GCObserver* p){
	if(gcobservers_current_==gcobservers_end_){
		expand_simple_dynamic_pointer_array((void**&)gcobservers_begin_, (void**&)gcobservers_end_, (void**&)gcobservers_current_);
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


}
