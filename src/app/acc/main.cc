#include <base/component.h>
#include <acc/acc.h>
#include <nic/packet_allocator.h>
#include <lwip/genode.h>
extern "C" {
	#include <lwip/sockets.h>
	#include <lwip/api.h>
}

Genode::size_t Component::stack_size() { return 64*1024; }

void Component::construct(Genode::Env &)
{
	enum { BUF_SIZE = Nic::Packet_allocator::DEFAULT_PACKET_SIZE * 128 };
	
	char ip_address[16] = "10.200.40.12";
	char subnet[16] = "10.255.255.255";
	char gateway[16] = "10.200.40.10";

	lwip_nic_init(inet_addr(ip_address),
				  inet_addr(subnet),
				  inet_addr(gateway),
				  BUF_SIZE,
				  BUF_SIZE);
				  
	acc acc("acc");
}
