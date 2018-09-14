#include <stdio.h>
#include <inttypes.h>

#include "net/sock/udp.h"
#include "xtimer.h"

int main(void)
{
    uint8_t buf[128];

    sock_udp_ep_t local = SOCK_IPV6_EP_ANY;
    sock_udp_t sock;

    local.port = 12345;

    (void) puts("Welcome to RIOT! - running UDP echo server");
    
    if (sock_udp_create(&sock, &local, NULL, 0) < 0) {
        puts("Error: Unable create sock.");
        return -1;
    }

    while (1) {
        sock_udp_ep_t remote;
        char remote_addr[IPV6_ADDR_MAX_STR_LEN];
        ssize_t res;

        if ((res = sock_udp_recv(&sock, buf, sizeof(buf), SOCK_NO_TIMEOUT,
                        &remote)) >= 0) {
            ipv6_addr_to_str(remote_addr, (const ipv6_addr_t *)&remote.addr.ipv6,
                    IPV6_ADDR_MAX_STR_LEN);
            printf("Received message '%s' from %s\n", buf, remote_addr);

            /* wait a second before reply */
            xtimer_sleep(1);

            if (sock_udp_send(&sock, buf, res, &remote) < 0) {
                puts("Error sending reply");
            }
            puts("Sent reply");
        }
    }
    
    return 0;
}
