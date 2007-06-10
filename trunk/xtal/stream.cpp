
#include "xtal.h"
#include "streamimpl.h"

namespace xtal{

void InitStream(){
	TClass<Stream> cls("Stream");
	cls.method("p8", &Stream::p8);
	cls.method("p16", &Stream::p16);
	cls.method("p32", &Stream::p32);
	cls.method("s8", &Stream::s8);
	cls.method("s16", &Stream::s16);
	cls.method("s32", &Stream::s32);
	cls.method("u8", &Stream::u8);
	cls.method("u16", &Stream::u16);
	cls.method("u32", &Stream::u32);
	
	cls.method("read", (String (Stream::*)(uint_t) const)&Stream::read);
	cls.method("write", (uint_t (Stream::*)(const String&) const)&Stream::write);
	cls.method("seek", &Stream::seek).param(null, Named("whence", Stream::XSEEK_SET));
	cls.method("inpour", &Stream::inpour);

	cls.method("iter_first", &Stream::iter_first);
	cls.method("iter_next", &Stream::iter_next);
	cls.method("iter_break", &Stream::iter_break);

	cls.def("SEEK_SET", Stream::XSEEK_SET);
	cls.def("SEEK_CUR", Stream::XSEEK_CUR);
	cls.def("SEEK_END", Stream::XSEEK_END);
}

void InitMemoryStream(){
	TClass<MemoryStream> cls("MemoryStream");
	cls.inherit(TClass<Stream>::get());
	cls.def("new", New<MemoryStream>());
	cls.method("to_s", &MemoryStream::to_s);
}

void InitFileStream(){
	TClass<FileStream> cls("FileStream");
	cls.inherit(TClass<Stream>::get());
	cls.def("new", New<FileStream, const String&, const String&>());
}

Stream::Stream(){

}

void Stream::p8(int_t v) const{
	impl()->p8(v);
}

void Stream::p16(int_t v) const{
	impl()->p16(v);
}

void Stream::p32(int_t v) const{
	impl()->p32(v);
}

int_t Stream::s8() const{
	return impl()->s8();
}

int_t Stream::s16() const{
	return impl()->s16();
}

int_t Stream::s32() const{
	return impl()->s32();
}

uint_t Stream::u8() const{
	return impl()->u8();
}

uint_t Stream::u16() const{
	return impl()->u16();
}

uint_t Stream::u32() const{
	return impl()->u32();
}

uint_t Stream::tell() const{
	return impl()->tell();
}
	
uint_t Stream::write(const void* p, uint_t size) const{
	return impl()->do_write(p, size);
}
	
uint_t Stream::read(void* p, uint_t size) const{
	return impl()->do_read(p, size);
}

uint_t Stream::write(const String& str) const{
	return write(str.c_str(), str.length());
}

String Stream::read(uint_t size) const{
	char* buf = (char*)user_malloc(size+1);
	uint_t len = impl()->do_read(buf, size);
	buf[len] = 0;
	return String(buf, len, size+1, String::delegate_memory_t());
}

void Stream::seek(int_t offset, int_t whence) const{
	impl()->seek(offset, whence);
}

void Stream::close() const{
	impl()->close();
}

uint_t Stream::inpour(const Stream& in_stream, uint_t size) const{
	return impl()->inpour(in_stream, size);
}

void Stream::iter_first(const VMachine& vm){
	return impl()->iter_first(vm);
}

void Stream::iter_next(const VMachine& vm){
	return impl()->iter_next(vm);
}

void Stream::iter_break(const VMachine& vm){
	return impl()->iter_break(vm);
}

FileStream::FileStream(const String& filename, const String& mode)
:Stream(null){
	new(*this) FileStreamImpl(filename, mode);
}

MemoryStream::MemoryStream()
:Stream(null){
	new(*this) MemoryStreamImpl();
}

MemoryStream::MemoryStream(const void* data, uint_t data_size)
:Stream(null){
	new(*this) MemoryStreamImpl(data, data_size);
}

String MemoryStream::to_s() const{
	return impl()->to_s();
}

void* MemoryStream::data() const{
	return impl()->data();
}

}
