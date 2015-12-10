#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <net/ethernet.h>
#include <time.h>
#include <string.h>

int main(int argc, char **argv) {

    int f;
    struct ip *ip;

    char *pacote = calloc(1024 * 10, 1);

    f = open(argv[1], O_RDONLY);

    if (f < 0) {
        printf("Passe o arquivo como parâmetro\n");
        exit(1);
    }

    read(f, pacote, 1024 * 10);

    ip = (struct ip *) pacote;

    printf("IP Version: %d\n", ip->ip_v);
    printf("Header length: %d\n", ip->ip_hl * 4);
    printf("ToS: %d\n", ip->ip_tos);
    printf("Total length: %d\n", ntohs(ip->ip_len));
    printf("ID: %x\n", ntohs(ip->ip_id));
    printf("F. off: (flags) %x - (off) %d\n", (ntohs(ip->ip_off) & (IP_RF | IP_DF | IP_MF)) >> 13,
            (ntohs(ip->ip_off) & IP_OFFMASK) * 8);
    printf("ttl: %d\n", ip->ip_ttl);
    printf("Prot.: %d\n", ip->ip_p);
    printf("Checksum.: %x\n", ntohs(ip->ip_sum));
    printf("src ip: %s\n", inet_ntoa(ip->ip_src));
    printf("dst ip: %s\n", inet_ntoa(ip->ip_dst));

    if ((ntohs(ip->ip_off) & IP_OFFMASK) * 8 == 0) {
        printf("\n\nPrimeiro fragmento\n\n");
        struct udphdr *ffrag = (struct udphdr *) ((char *) ip + (ip->ip_hl * 4));

        printf("Src port: %d\n", ntohs(ffrag->uh_sport));
        printf("Dst port: %d\n", ntohs(ffrag->uh_dport));
        printf("Length: %d\n", ntohs(ffrag->uh_ulen));
        printf("chksum: %x\n", ntohs(ffrag->uh_sum));
    }

    printf("\n");
    printf("\n");
    printf("\n");

    int i;
    for (i = 0; i < 76; i++) {
        printf("%d\n", ip->ip_off);
        ip++;
    }

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    
    FILE* file = fopen(argv[1], "r");
    while (1) {
        fread(pacote, sizeof(ip), 1, file);
        if (feof(file)) {
            break;
        }
        ip = (struct ip *) pacote;
        printf("%d: %d + %d\n", ip->ip_id, ip->ip_off, ip->ip_len);
    }

    return (0);
}