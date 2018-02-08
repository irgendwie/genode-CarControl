#include <base/component.h>
#include <savm/savm.h>

Genode::size_t Component::stack_size() { return 64*1024; }

void Component::construct(Genode::Env &)
{
	savm savm;
}
