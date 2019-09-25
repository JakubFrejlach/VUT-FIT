#include "ipk-scan.h"

// FLAGS for argument parsing
bool address_flag = false;
bool tcp_flag = false;
bool udp_flag = false;
bool interface_flag = false;

using namespace std;

/*
 * Counts check sum for TCP/IP headers
 *
 * @param buf
 * @param nwords
 * @return              returns check sum
 */
unsigned short check_sum(unsigned short *buf, int nwords)
{
  // source: https://www.tenouk.com/Module43a.html
  unsigned long sum;
  for(sum=0; nwords>0; nwords--)
  {
    sum += *buf++;
  }
  sum = (sum >> 16) + (sum &0xffff);
  sum += (sum >> 16);
  return (unsigned short)(~sum);
}

/*
 * Converts ipv6 address in string to struct in6_addr
 *
 * @param str_address   address as string
 * @return              returns address as struct in6_addr
 */
struct in6_addr convert_IPv6(char *str_address)
{
  /***************************************************************************************
   *    Title: IPv6 parsing in C
   *    Author: user of stackoverflow with nickname "dreamlax" -> https://stackoverflow.com/users/10320/dreamlax
   *    Date: 18.4.2019
   *    Code version: 1
   *    Availability: https://stackoverflow.com/questions/2962664/ipv6-parsing-in-c
   ***************************************************************************************/
  struct in6_addr result;
  inet_pton(AF_INET6, str_address, &result);
  return result;
}

/*
 * Fills udphdr struct with data
 *
 * @param header   struct udphdr
 */
void UDP_header(struct udphdr* header, struct address_data a_data, int port)
{
  // source: https://www.tenouk.com/Module43a.html
  header->uh_sport = htons(SOURCE_PORT);
  header->uh_dport = htons(port);
  header->uh_ulen = htons(sizeof(struct udphdr));
}

/*
 * Fills tcphdr struct with data
 *
 * @param header   struct tcphdr
 */
void TCP_header(struct tcphdr* header, struct address_data a_data, int port)
{
  // source: https://www.tenouk.com/Module43a.html
  header->th_sport = htons(SOURCE_PORT);
  header->th_dport = htons(port);
  header->th_seq = htonl(1);
  header->th_ack = 0;
  header->th_x2 = 0;
  header->th_off = 5;
  header->th_flags = TH_SYN;
  header->th_win = htons(32767);
  header->th_sum = 0;
  header->th_urp = 0;
}

/*
 * Fills ip struct with data
 *
 * @param header   struct ip
 */
void IP_header(struct ip* header, struct address_data a_data, int type)
{
  // source: https://www.tenouk.com/Module43a.html
  header->ip_v = 4;
  header->ip_hl = 5;
  header->ip_tos = 16;
  if(type == TCP)
  {
    header->ip_p = 6; // TCP -> 6/UDP -> 17
    header->ip_len = sizeof(struct ip) + sizeof(struct tcphdr);
  }
  else if(type == UDP)
  {
    header->ip_p = 17; // TCP -> 6/UDP -> 17
    header->ip_len = sizeof(struct ip) + sizeof(struct udphdr);
  }
  header->ip_id = htons(54321);
  header->ip_off = 0;
  header->ip_ttl = 64;
  header->ip_sum = 0;
  header->ip_src.s_addr = inet_addr(a_data.source_address_ipv4.c_str());
  header->ip_dst.s_addr = inet_addr(a_data.host_ipv4.c_str());
}

/*
 * Creates socket of specified type (UDP/TCP)
 *
 * @param socket_type   type of socket to be created
 * @param ip_type       type of IP address
 * @return              returns file descriptor of the socket
 */
int create_socket(int socket_type, int ip_type)
{
  // source: https://www.tenouk.com/Module43a.html
  int raw_sock;

  // TCP
  if(socket_type == TCP)
  {
    raw_sock = socket(ip_type, SOCK_RAW, IPPROTO_TCP);
    if(raw_sock < 0)
    {
      return raw_sock;
    }
  }
  // UDP
  else if(socket_type == UDP)
  {
    raw_sock = socket(ip_type, SOCK_RAW, IPPROTO_UDP);
    if(raw_sock < 0)
    {
      return raw_sock;
    }
  }

  // integer with value 1 for setsockopt
  int one = 1;
  int offset_udp = 6;  // offset in bytes for IPv6 UDP -> 128/8
  int offset_tcp = 16; // offset in bytes for IPv6 TCP -> 48/8
  int res;
  // IPv4 socket options
  if(ip_type == AF_INET)
  {
    if((res = setsockopt(raw_sock, IPPROTO_IP, IP_HDRINCL, &one, sizeof(one))))
    {
      return res;
    }
  }
  // IPv6 UDP socket options
  else if(ip_type == AF_INET6 and socket_type == UDP)
  {
    if((res = setsockopt(raw_sock, IPPROTO_IPV6, IPV6_CHECKSUM, &offset_udp, sizeof(offset_udp))))
    {
      return res;
    }
  }
  // IPv6 TCP socket options
  else if(ip_type == AF_INET6 and socket_type == TCP)
  {
    if((res = setsockopt(raw_sock, IPPROTO_IPV6, IPV6_CHECKSUM, &offset_tcp, sizeof(offset_tcp))))
    {
      return res;
    }
  }
  return raw_sock;
}

/*
 * Prings debug info
 *
 * @param a_data    structure with addresses
 */
void debug_info(struct address_data a_data)
{
  cout << "************* DEBUG INFO *************" << endl;
  cout << "Domain: " << a_data.domain << endl;
  cout << "Source IPv4 address: " << a_data.source_address_ipv4 << endl;
  cout << "Source IPv6 address: " << a_data.source_address_ipv6 << endl;
  cout << "Host IPv4 address: " << a_data.host_ipv4 << endl;
  cout << "Host IPv6 address: " << a_data.host_ipv6 << endl;
  cout << "Interface: " << a_data.interface << endl;
  cout << "TCP ports: ";
  for (auto const& c : a_data.tcp_ports)
    std::cout << c << ", ";
  cout << endl;
  cout << "UDP ports: ";
  for (auto const& c : a_data.udp_ports)
    std::cout << c << ", ";
  cout << endl;
}

/*
 * Get source address from interface
 *
 * @param interface    string with interface name
 * @param type         type of IP address
 * @return             returns string with interface address
 */
string get_source_address(char *interface, int type)
{
  // not whole code taken, just some basic facts and "know-how"
  /***************************************************************************************
   *    Title: How can I get to know the IP address for interfaces in C?
   *    Author: Christopher C. Aycock -> https://github.com/chrisaycock
   *    Date: 17.4.2019
   *    Code version: 1
   *    Availability: https://stackoverflow.com/questions/4139405/how-can-i-get-to-know-the-ip-address-for-interfaces-in-c
   ***************************************************************************************/
  struct ifaddrs *ifa, *ifa_tmp; // structures for getifaddrs
  char addr[50] = { 0 };         // buffer for address

  // obtain address
  if(getifaddrs(&ifa))
  {
    cerr << "ERROR:Unable to get source address." << endl;
    exit(EXIT_FAILURE);
  }

  // search all interfaces
  for(ifa_tmp = ifa; ifa_tmp != NULL; ifa_tmp = ifa_tmp->ifa_next)
  {
    // find IP address type and interface
    if(ifa_tmp->ifa_addr->sa_family == type and !strcmp(ifa_tmp->ifa_name, interface))
    {
      // convert IPv4 address
      if(type == AF_INET)
      {
        struct sockaddr_in *in = (struct sockaddr_in*)ifa_tmp->ifa_addr;
        inet_ntop(AF_INET, &in->sin_addr, addr, sizeof(addr));
        break;
      }
      // convert IPv6 address
      else if(type == AF_INET6)
      {
        struct sockaddr_in6 *in6 = (struct sockaddr_in6*)ifa_tmp->ifa_addr;
        inet_ntop(AF_INET6, &in6->sin6_addr, addr, sizeof(addr));
        break;
      }
    }
  }

  // free getifaddrs resources
  freeifaddrs(ifa);
  return addr;
}

/*
 * If interface is not given via. -i argument, searches for first
 * RUNNING, UP and not LOOPBACK
 *
 * @param interface    string to store the interface
 */
string get_interface(string interface)
{
  // if no interface given, search for it
  if(interface.empty())
  {
    struct ifaddrs *ifap;

    // get list of all interfaces
    if(getifaddrs(&ifap))
    {
      cerr << "ERROR:Could not resolve interface." << endl;
      exit(EXIT_FAILURE);
    }
    // search all interfaces
    for(struct ifaddrs *p = ifap; p != NULL; p = p->ifa_next)
    {
      // first interface that is not LOOPBACK, is UP and is RUNNING
      if(!(p->ifa_flags & IFF_LOOPBACK) and (p->ifa_flags & IFF_UP) and (p->ifa_flags & IFF_RUNNING))
      {
        string name = p->ifa_name;
        // free getifaddrs resources
        freeifaddrs(ifap);
        return name;
      }
    }
  }
  return interface;
}

/*
 * Gets IP address from domain name
 *
 * @param ipv_type    type of IP address to resolve
 * @param domain      C like string with domain
 * @return            resolved IP address
 */
string get_domain_address(int ipv_type, char *domain)
{
  // source: http://man7.org/linux/man-pages/man3/getaddrinfo.3.html
  // fill hints for getaddrinfo
  struct addrinfo hints, *infoptr;
  memset(&hints, 0, sizeof(struct addrinfo));

  hints.ai_family = AF_UNSPEC; // IPv4/IPv6
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;
  hints.ai_protocol = 0;

  // get address info and check result
  int result = getaddrinfo(domain, NULL, &hints, &infoptr);
  if(result)
  {
    cerr << "ERROR:" << gai_strerror(result) << endl;
    exit(EXIT_FAILURE);
  }

  /***************************************************************************************
   *    Title: Networking, Part 2: Using getaddrinfo
   *    Author: Lawrence Angrave
   *    Date: 17.4.2019
   *    Code version: 9
   *    Availability: https://github.com/angrave/SystemProgramming/wiki/Networking,-Part-2:-Using-getaddrinfo
   ***************************************************************************************/
   // search for first address that matches ipv_type
  char host[256] = { 0 };
  for(struct addrinfo *p = infoptr; p != NULL; p = p->ai_next)
  {
    if(p->ai_family == ipv_type)
    {
      getnameinfo(p->ai_addr, p->ai_addrlen, host, sizeof (host), NULL, 0, NI_NUMERICHOST);
      break;
    }
  }

  // free getaddrinfo resources
  freeaddrinfo(infoptr);
  return host;
}

/*
 * Converts C++ string to C like string (char *)
 *
 * @param str       string to convert
 * @return          converted string
 */
char *c_string(string str)
{
  char *cstr = &str[0u];
  return cstr;
}

/*
 * Initializes regex with pattern
 *
 * @param regex     pointer to regex
 * @param pattern   pattern of regex
 */
void init_regex(regex_t *regex, char *pattern)
{
  if(regcomp(regex, pattern, REG_EXTENDED|REG_NOSUB))
  {
    cerr << "ERROR:Failed to compile regex." << endl;
    exit(EXIT_FAILURE);
  }
}

/*
 * Parses argument with port numbers and returns them as vector of integers
 *
 * @param ports_arg     all port numbers in array of chars (string)
 * @return              vector of integers (numbers of ports)
 */
vector<int> handle_ports(char* ports_arg)
{
  vector<int> ports;
  regex_t regex;

  // ports are given via range of ports like 1-65535
  init_regex(&regex, (char*)"^[[:digit:]]+-[[:digit:]]+$");
  if(!regexec(&regex, ports_arg, 0, NULL, 0))
  {
    // split by '-'
    int range1 = stoi(strtok(ports_arg, "-"));
    int range2 = stoi(strtok(NULL, "-"));

    // push every port number in given range to ports vector
    for(;range1 <= range2; range1++)
    {
      ports.push_back(range1);
    }
    regfree(&regex);
    return ports;
  }
  regfree(&regex);

  // ports are given via list like 1,23,45,60,etc
  init_regex(&regex, (char*)"^[[:digit:]]+(,[[:digit:]]+)*$");
  if(!regexec(&regex, ports_arg, 0, NULL, 0))
  {
    // split by ','
    char *s = strtok(ports_arg, ",");

    // push every given port number to ports vector
    while(s)
    {
      ports.push_back(stoi(s));
      s = strtok(NULL, ",");
    }
    regfree(&regex);
    return ports;
  }

  // Unknown port format -> ERROR
  cerr << "ERROR:Invalid ports format given." << endl;
  exit(EXIT_FAILURE);
}


/*
 * Process IPv6 UDP and TCP scanning for all given ports on given address
 *
 * @param a_data        structure with addresses and ports
 */
void ipv6_process(struct address_data a_data)
{
  char error_buffer[PCAP_ERRBUF_SIZE];  // error buffer for pcap handling
  int res;                              // variable for pcap_next_ex result
  struct bpf_program fp;                // structure for pcap filter compiling
  const u_char *packet;                 // buffer for packet
  struct pcap_pkthdr *pcap_hdr;         // structure for pcap_next_ex
  struct udphdr *udp_h;                 // udp structure for packet creating
  struct tcphdr *tcp_h;                 // tcp structure for packet creating
  struct tcphdr *aux_tcp_h;             // tcp structure for maping to received socket
  char buffer[PCKT_LEN];                // buffer for creating packet

  // create pcap handler and initialize it, set timeout and set immediate mode for capturing
  pcap_t *handle = pcap_create(a_data.interface.c_str(), error_buffer);
  pcap_set_timeout(handle, 1000);
  pcap_set_immediate_mode(handle, 1);
  pcap_activate(handle);

  // initialize structure for packet sending
  struct sockaddr_in6 sockin;
  sockin.sin6_family = AF_INET6;
  sockin.sin6_port = 0;
  sockin.sin6_scope_id = 0;
  sockin.sin6_flowinfo = 0;
  sockin.sin6_addr = convert_IPv6((char *)a_data.host_ipv6.c_str());

  // create raw socket for TCP
  int raw_sock = create_socket(TCP, AF_INET6);
  if(raw_sock < 0)
  {
    cerr << "ERROR:Failed to create raw socket." << endl;
    pcap_close(handle);
    exit(EXIT_FAILURE);
  }

  for(const auto& port : a_data.tcp_ports)
  {
    // set filter for TCP with specified the port
    pcap_compile(handle, &fp, ("ip6 and tcp and ((ip6[53] & 0x14 == 0x14) or (ip6[53] & 0x12 == 0x12)) and ip6[42:2] == "
     + to_string(SOURCE_PORT) + " and ip6[40:2] == " + to_string(port) + " and src " + a_data.host_ipv6 + " and dst " + a_data.source_address_ipv6).c_str(), 0, PCAP_NETMASK_UNKNOWN);
    pcap_setfilter(handle, &fp);
    pcap_freecode(&fp);

    // clear buffers
    memset(buffer, 0, PCKT_LEN);

    // fill buffer with tcp structure
    tcp_h = (struct tcphdr *)buffer;

    // fill TCP header
    TCP_header(tcp_h, a_data, port);

    // send and catch packet
    for(int packet_sent = 0; packet_sent <= MAX_ATTEMPTS_TCP; packet_sent++)
    {
      if((sendto(raw_sock, buffer, sizeof(struct tcphdr), 0, (struct sockaddr *)&sockin, sizeof(struct sockaddr_in6))) < 0)
      {
        cerr << "ERROR:Failed to send." << endl;
        pcap_close(handle);
        exit(EXIT_FAILURE);
      }

      res = pcap_next_ex(handle, &pcap_hdr, &packet);
      if(res > 0)
      {
        // map tcp header to received socket
        aux_tcp_h = (struct tcphdr*)(packet + sizeof(struct ip6_hdr) + sizeof(struct ether_header));

        // TH_SYN and TH_ACK flags set -> open port
        if((aux_tcp_h->th_flags & TH_SYN) and (aux_tcp_h->th_flags & TH_ACK))
        {
          cout << port <<"/tcp\topen" << endl;
          break;
        }
        // TH_RST and TH_ACK flags set -> closed port
        else if((aux_tcp_h->th_flags & TH_RST) and (aux_tcp_h->th_flags & TH_ACK))
        {
          cout << port << "/tcp\tclosed" << endl;
          break;
        }
      }
      // no received packet after 2 attempts -> filtered port
      else if(!res and packet_sent == MAX_ATTEMPTS_TCP)
      {
        cout << port <<"/tcp\tfiltered" << endl;
      }
      // no received packet -> another attempt
      else if(!res)
      {
        continue;
      }
      else
      {
        cerr << "ERROR:Failed to receive." << endl;
        pcap_close(handle);
        exit(EXIT_FAILURE);
      }
    }
  }

  // set filter for UDP (icmp6 answers)
  pcap_compile(handle, &fp, ("icmp6 and ip6[40] == 1 and src " + a_data.host_ipv6 + " and dst " + a_data.source_address_ipv6).c_str(), 0, PCAP_NETMASK_UNKNOWN);
  pcap_setfilter(handle, &fp);
  pcap_freecode(&fp);

  // create raw socket for UDP
  raw_sock = create_socket(UDP, AF_INET6);
  if(raw_sock < 0)
  {
    cerr << "ERROR:Failed to create raw socket." << endl;
    pcap_close(handle);
    exit(EXIT_FAILURE);
  }

  for(const auto& port : a_data.udp_ports)
  {
    // clear buffer
    memset(buffer, 0, PCKT_LEN);

    // fill buffer with udp structure
    udp_h = (struct udphdr *)buffer;

    // fill UDP header
    UDP_header(udp_h, a_data ,port);

    // send and catch packet
    for(int packet_sent = 0; packet_sent <= MAX_ATTEMPTS_UDP; packet_sent++)
    {
      if((sendto(raw_sock, buffer, sizeof(struct udphdr), 0, (struct sockaddr *)&sockin, sizeof(sockaddr_in6))) < 0)
      {
        cerr << "ERROR:Failed to send." << endl;
        pcap_close(handle);
        exit(EXIT_FAILURE);
      }

      int res = pcap_next_ex(handle, &pcap_hdr, &packet);
      // no answer and enough attempts
      if(!res and packet_sent == MAX_ATTEMPTS_UDP)
      {
        cout << port << "/UDP\topen" << endl;
        break;
      }
      // answer -> closed port
      else if(res > 0)
      {
        cout << port << "/UDP\tclosed" << endl;
        break;
      }
      // pcap failed
      else if(res < 0)
      {
        cerr << "ERROR:Failed to receive." << endl;
        pcap_close(handle);
        exit(EXIT_FAILURE);
      }
    }
  }
  pcap_close(handle);
}

/*
 * Process IPv4 UDP and TCP scanning for all given ports on given address
 *
 * @param a_data        structure with addresses and ports
 */
void ipv4_process(struct address_data a_data)
{
  // Basic facts taken from:
  /***************************************************************************************
   *    Title: Using libpcap in C
   *    Author: user of devdungeon.cpm with nickname "NanoDano" ->  https://www.devdungeon.com/users/nanodano
   *    Date: 17.4.2019
   *    Code version: 1
   *    Availability: https://www.devdungeon.com/content/using-libpcap-c
   ***************************************************************************************/
  char error_buffer[PCAP_ERRBUF_SIZE]; // error buffer for pcap handling
  int res;                             // variable for pcap_next_ex result
  struct bpf_program fp;               // structure for pcap filter compiling
  const u_char *packet;                // buffer for packet
  struct pcap_pkthdr *pcap_hdr;        // structure for pcap_next_ex
  struct ip *ip_h;                     // ip structure for packet creating
  struct udphdr *udp_h;                // udp structure for packet creating
  struct tcphdr *tcp_h;                // tcp structure for packet creating
  struct tcphdr *aux_tcp_h;            // tcp structure for maping to received socket
  struct pseudo_tcp_header *p_tcp_hdr; // pseudo_tcp_header for tcp checksum

  // buffers for creating packet
  char buffer[PCKT_LEN];
  char aux_buffer[PCKT_LEN];

  // create pcap handler and initialize it, set timeout and set immediate mode for capturing
  pcap_t *handle = pcap_create(a_data.interface.c_str(), error_buffer);
  pcap_set_timeout(handle, 1000);
  pcap_set_immediate_mode(handle, 1);
  pcap_activate(handle);

  // initialize structure for packet sending
  struct sockaddr_in sockin;
  sockin.sin_family = AF_INET;
  sockin.sin_port = 0;
  sockin.sin_addr.s_addr = inet_addr(a_data.host_ipv4.c_str());

  // create raw socket for TCP
  int raw_sock = create_socket(TCP, AF_INET);
  if(raw_sock < 0)
  {
    cerr << "ERROR:Failed to create raw socket." << endl;
    pcap_close(handle);
    exit(EXIT_FAILURE);
  }

  // How to use sendto() taken from (just basic facts):
  /***************************************************************************************
   *    Title: sending custom tcp packet using sendto() in c?
   *    Author: user of stackoverflow with nickname "IwontDoIt" -> https://stackoverflow.com/users/9239345/iwontdoit
   *    Date: 17.4.2019
   *    Code version: 1
   *    Availability: https://stackoverflow.com/questions/48338190/sending-custom-tcp-packet-using-sendto-in-c
   ***************************************************************************************/
  // TCP scanning
  for(const auto& port : a_data.tcp_ports)
  {
    // set filter for TCP with specified the port
    pcap_compile(handle, &fp, ("(tcp[tcpflags] == (tcp-rst | tcp-ack)) or (tcp[tcpflags] == (tcp-syn | tcp-ack)) and dst port 7543 and src port " +
    to_string(port) + " and src " + a_data.host_ipv4 + " and dst " + a_data.source_address_ipv4).c_str(), 0, inet_addr(a_data.host_ipv4.c_str()));
    pcap_setfilter(handle, &fp);
    pcap_freecode(&fp);

    // clear buffers
    memset(buffer, 0, PCKT_LEN);
    memset(aux_buffer, 0, PCKT_LEN);

    // fill auxiliary buffer with tcp structure and buffer with ip structure
    tcp_h = (struct tcphdr *)aux_buffer;
    ip_h = (struct ip*)buffer;

    // fill IP and TCP headers
    IP_header(ip_h, a_data, TCP);
    TCP_header(tcp_h, a_data , port);

    // fill auxiliary buffer with pseudo tcp header
    p_tcp_hdr = (struct pseudo_tcp_header *)(aux_buffer + sizeof(struct tcphdr));

    // fill pseudo_tcp_header
    p_tcp_hdr->src_address = inet_addr(a_data.source_address_ipv4.c_str());
    p_tcp_hdr->dst_address = inet_addr((char*)a_data.host_ipv4.c_str());
    p_tcp_hdr->protocol = IPPROTO_TCP;
    p_tcp_hdr->len = htons(sizeof(struct tcphdr));

    // count tcp checksum and copy tcp header from auxiliary buffer to buffer
    tcp_h->th_sum = check_sum((unsigned short *)aux_buffer, (sizeof(struct pseudo_tcp_header) + sizeof(struct tcphdr)));
    memcpy(buffer + sizeof(struct ip), aux_buffer, sizeof(struct tcphdr));

    // count ip checksum
    ip_h->ip_sum = check_sum((unsigned short *)buffer, sizeof(struct ip) + sizeof(struct tcphdr));

    // send and catch packet
    for(int packet_sent = 0; packet_sent <= MAX_ATTEMPTS_TCP; packet_sent++)
    {
      if((sendto(raw_sock, buffer, ip_h->ip_len, 0, (struct sockaddr *)&sockin, sizeof(struct sockaddr_in))) < 0)
      {
        cerr << "ERROR:Failed to send." << endl;
        pcap_close(handle);
        exit(EXIT_FAILURE);
      }
      res = pcap_next_ex(handle, &pcap_hdr, &packet);
      if(res > 0)
      {
        // map tcp header to received socket
        aux_tcp_h = (struct tcphdr*)(packet + sizeof(struct ether_header) + sizeof(struct ip));

        // TH_SYN and TH_ACK flags set -> open port
        if((aux_tcp_h->th_flags & TH_SYN) and (aux_tcp_h->th_flags & TH_ACK))
        {
          cout << port <<"/tcp\topen" << endl;
          break;
        }
          // TH_RST and TH_ACK flags set -> closed port
        else if((aux_tcp_h->th_flags & TH_RST) and (aux_tcp_h->th_flags & TH_ACK))
        {
          cout << port << "/tcp\tclosed" << endl;
          break;
        }
      }
      // no received packet after 2 attempts -> filtered port
      else if(!res and packet_sent == MAX_ATTEMPTS_TCP)
      {
        cout << port <<"/tcp\tfiltered" << endl;
      }
      // no received packet -> another attempt
      else if(!res)
      {
        continue;
      }
      else
      {
        cerr << "ERROR:Failed to receive." << endl;
        pcap_close(handle);
        exit(EXIT_FAILURE);
      }
    }
  }

  // set pcap filter for UDP (icmp answers)
  pcap_compile(handle, &fp, ("icmp and icmp[icmptype] == icmp-unreach and src " + a_data.host_ipv4 +
  " and dst " + a_data.source_address_ipv4).c_str(), 0, inet_addr(a_data.host_ipv4.c_str()));
  pcap_setfilter(handle, &fp);
  pcap_freecode(&fp);

  // create raw socket for UDP
  raw_sock = create_socket(UDP, AF_INET);
  if(raw_sock < 0)
  {
    cerr << "ERROR:Failed to create raw socket." << endl;
    pcap_close(handle);
    exit(EXIT_FAILURE);
  }

  // UDP scanning
  for(const auto& port : a_data.udp_ports)
  {
    // clear buffer
    memset(buffer, 0, PCKT_LEN);

    // fill packet with ip and upd sctructures
    ip_h = (struct ip*)buffer;
    udp_h = (struct udphdr *)(buffer + sizeof(struct ip));

    // fill ip and udp headers
    IP_header(ip_h, a_data, UDP);
    UDP_header(udp_h, a_data , port);

    // send and catch packet
    for(int packet_sent = 0; packet_sent <= MAX_ATTEMPTS_UDP; packet_sent++)
    {
      if((sendto(raw_sock, buffer, ip_h->ip_len, 0, (struct sockaddr *)&sockin, sizeof(struct sockaddr_in6))) < 0)
      {
        cerr << "ERROR:Failed to send." << endl;
        pcap_close(handle);
        exit(EXIT_FAILURE);
      }
      res = pcap_next_ex(handle, &pcap_hdr, &packet);

      // no answer and enough attempts
      if(!res and packet_sent == MAX_ATTEMPTS_UDP)
      {
        cout << port << "/udp\topen" << endl;
        break;
      }
      // answer -> closed port
      else if(res > 0)
      {
        cout << port << "/udp\tclosed" << endl;
        break;
      }
      // pcap failed
      else if(res < 0)
      {
        cerr << "ERROR:Failed to receive." << endl;
        pcap_close(handle);
        exit(EXIT_FAILURE);
      }
    }
  }
  // free pcap resources
  pcap_close(handle);
}

int main(int argc, char **argv)
{
  struct address_data a_data;

  static struct option long_options[] =
  {
    {"pt", required_argument, 0, 'a'},
    {"pu", required_argument, 0, 'b'},
    {"i", required_argument, 0, 'c'},
    {"help", no_argument, 0, 'd'},
    {0, 0, 0, 0}
  };

  // getopt variables
  int option_parsed;
  int option_index = 0;

  // arguments with tcp and udp ports
  string tcp_ports_arg, udp_ports_arg;


  // loop through all agruments using getopt_long_only function
  while((option_parsed = getopt_long_only(argc, argv, "abc", long_options, &option_index)) != -1)
  {
    switch(option_parsed)
    {
      // tcp ports
      case 'a':
        if(tcp_flag)
        {
          cerr << "ERROR:Unknown program param." << endl;
          return EXIT_FAILURE;
        }
        else
        {
          tcp_flag = true;
          tcp_ports_arg = optarg;
        }
        break;
      // udp ports
      case 'b':
        if(udp_flag)
        {
          cerr << "ERROR:Unknown program param." << endl;
          return EXIT_FAILURE;
        }
        else
        {
          udp_flag = true;
          udp_ports_arg = optarg;
        }
        break;
      // optional interface
      case 'c':
        if(interface_flag)
        {
          cerr << "ERROR:Unknown program param." << endl;
          return EXIT_FAILURE;
        }
        else
        {
          interface_flag = true;
          a_data.interface = optarg;
        }
        break;
      // help option
      case 'd':
        if(argc == 2)
        {
          cout << "****************************** HELP ******************************" << endl;
          cout << "* Program scans given UDP/TCP ports on given domain/IPv4 address/IPv6 address" << endl;
          cout << "* and identifies them as closed/open (UDP ports) or clsoed/open/filtered (TCP ports)" << endl;
          cout << "*" << endl;
          cout << "* Program must be executed as root (su/sudo) and may be executed with following arguments:" << endl;
          cout << "* ./ipk-scan {-i <interface>} -pu <port-ranges> -pt <port-ranges> [<domain-name> | <IP-address>]" << endl;
          cout << "* -i <interface>\toptional argument that sepcifies, which interface should be used, if not given," << endl;
          cout << "* \t\t\tprogram uses first non loopback interface" << endl;
          cout << "* At least one from -pu, -pt argument is required" << endl;
          cout << "* -pu <port-ranges>\tspcifies which udp ports should be scanned (for example 1,2,3,4,5 or 1-5)" << endl;
          cout << "* -pt <port-ranges>\tspcifies which tcp ports should be scanned (for example 1,2,3,4,5 or 1-5)" << endl;
          cout << "* [<domain-name> | <IP-address>]\tspecifies address or domain to be scanned" << endl;
          cout << "*" << endl;
          cout << "* For help, use (this argument cannot be combined with others):" << endl;
          cout << "* ./ipk-scan -help" << endl;
          return EXIT_SUCCESS;
        }
        else
        {
          cerr << "ERROR:Invalid params combination." << endl;
          return EXIT_FAILURE;
        }
        break;
      // unknown option
      default:
        cerr << "ERROR:Unknown program param." << endl;
        return EXIT_FAILURE;
    };
  }

  // search for non option arguments (IP address or domain name)
  for (int i = optind; i < argc; i++)
  {
    if(!address_flag)
    {
      address_flag = true;
    }
    // two non option argument given -> ERROR
    else
    {
      cerr << "ERROR:Unknown program param." << endl;
      return EXIT_FAILURE;
    }
    a_data.domain = argv[i];
  }

  if(!address_flag)
  {
    cerr << "ERROR:Domain or address not given." << endl;
    return EXIT_FAILURE;
  }

  if(!tcp_flag and !udp_flag)
  {
    cerr << "ERROR:No ports given." << endl;
    return EXIT_FAILURE;
  }

  // no tcp or udp ports given
  if(!tcp_flag and !udp_flag)
  {
    return EXIT_SUCCESS;
  }
  // load ports to vectors
  if(tcp_flag)
  {
    a_data.tcp_ports = handle_ports((char *)tcp_ports_arg.c_str());
  }
  if(udp_flag)
  {
    a_data.udp_ports = handle_ports((char *)udp_ports_arg.c_str());
  }

  if(a_data.tcp_ports.empty() and a_data.udp_ports.empty())
  {
    cerr << "ERROR:No ports given." << endl;
    return EXIT_FAILURE;
  }
  // resolve IP addresses from domain name
  a_data.host_ipv4 = get_domain_address(AF_INET, (char *)a_data.domain.c_str());
  a_data.host_ipv6 = get_domain_address(AF_INET6, (char *)a_data.domain.c_str());

  // if not given, searches for interface
  a_data.interface = get_interface(a_data.interface);

  // get source address from interface
  a_data.source_address_ipv4 = get_source_address((char *)a_data.interface.c_str(), AF_INET);
  a_data.source_address_ipv6 = get_source_address((char *)a_data.interface.c_str(), AF_INET6);

  // Initialize output with domain name
  cout << "Interesting ports on " << a_data.domain << endl;
  if(!a_data.source_address_ipv4.empty() and !a_data.host_ipv4.empty())
  {
    // Initialize output with IPv4 address
    cout << "Target IPv4 address: " << a_data.host_ipv4 << endl;
    cout << "PORT\tSTATUS" << endl;
    ipv4_process(a_data);
  }
  else if(!a_data.source_address_ipv6.empty() and !a_data.host_ipv6.empty())
  {
    // Initialize output with IPv6 address
    cout << "Target IPv6 address: " << a_data.host_ipv6 << endl;
    cout << "PORT\tSTATUS" << endl;
    ipv6_process(a_data);
  }
  else
  {
    cerr << "ERROR:No available source adrress/target address couple." << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
