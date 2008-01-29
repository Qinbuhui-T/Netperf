/*
        Copyright (C) 1993-2004 Hewlett-Packard Company
*/

 /* This file contains the test-specific definitions for netperf's BSD */
 /* sockets tests */

/* well boys and girls, seems that while AF_INET is "2" and AF_UNSPEC
   is "0" the world over, AF_INET6 is different values depending on
   the platform... grrr.  On HP-UX 11i it is "22" and on Linux 2.6 it
   is "10" sooooo... we have to define our own space for netperf to
   enable us to pass values around from machine to machine. raj
   2005-02-08 */
#define NF_UNSPEC 0
#define NF_INET   4
#define NF_INET6  6

/* it would also seem that the socket type defines differ from
   platform to platform, which means we need to define our own values
   to pass between netperf and netserver so they can be translated to
   the local versions.  NST == Netperf Socket Type raj 2008-01-14 */
#define NST_UNKN   -1
#define NST_STREAM 1
#define NST_DGRAM  2

#ifdef WANT_OMNI
struct  omni_request_struct {
  int32_t    send_buf_size;         /* SO_SNDBUF */
  uint32_t   send_size;             /* bytes per send() call */
  uint32_t   send_alignment;        /* alignment of send buffer */
  uint32_t   send_offset;           /* offset from send alignment */
  uint32_t   send_width;            /* number of send buffers to use */
  int32_t    request_size;          /* size of a request */

  int32_t    recv_buf_size;         /* SO_RCVBUF */
  uint32_t   receive_size;          /* size of buffers in recv */
  uint32_t   recv_alignment;        /* alignment of recv buffer */
  uint32_t   recv_offset;           /* offset from recv alignment */
  uint32_t   recv_width;            /* number of recv buffers to use */
  int32_t    response_size;         /* size of a response */

  uint32_t   no_delay;              /* do we set mumble_NODELAY? */
  uint32_t   use_sendfile;          /* use sendfile rather than send? */
  uint32_t   connect_test;          /* does the test include connect? */

  uint32_t   measure_cpu;    /* do we measure CPU? */
  float      cpu_rate;       /* do we know how fast the cpu is already? */

  int32_t    test_length;    /* how long is the test? */

  uint32_t   so_rcvavoid;    /* avoid copies on recv? */
  uint32_t   so_sndavoid;    /* avoid copies on send? */
  uint32_t   send_dirty_count; /* bytes to dirty before calling send */
  uint32_t   recv_dirty_count; /* bytes to dirty before calling recv */
  uint32_t   recv_clean_count; /* bytes to access before calling recv */

  uint32_t   checksum_off;  /* should checksums be disabled? */
  uint32_t   data_port;     /* what port number should netserver use? */
  uint32_t   ipfamily;      /* address family of the data connection */
  uint32_t   socket_type;   /* dgram? stream? other? */
  uint32_t   protocol;      /* the protocol of the data connection */
  uint32_t   direction;     /* which way flows the data? */
  uint32_t   netperf_port;  /* when netserver needs netperf's data port */
  uint32_t   ipaddr[4];     /* when netserver needs netperf's data IP */
};

struct  omni_response_struct {
  int32_t    recv_buf_size;
  uint32_t   receive_size;

  int32_t    send_buf_size;
  uint32_t   send_size;

  uint32_t   no_delay;
  uint32_t   use_sendfile;

  uint32_t   measure_cpu;
  float      cpu_rate;

  uint32_t   test_length;

  uint32_t   so_rcvavoid;
  uint32_t   so_sndavoid;

  uint32_t   data_port;     /* connect to this port number */
};

struct omni_results_struct {
  double     bytes_received;
  uint32_t   recv_calls;
  int32_t    recv_buf_size; /* SO_RCVBUF at end of test */

  double     bytes_sent;
  uint32_t   send_calls;
  int32_t    send_buf_size; /* SO_SNDBUF at end of test */
  uint32_t   failed_sends;
  uint32_t   trans_received; 

  float      elapsed_time;  /* length of test in seconds */

  float      cpu_util;
  float      serv_dem;
  uint32_t   cpu_method;    /* how was CPU util measured? */
  uint32_t   num_cpus;      /* number of CPUs in remote */
};

#endif /* WANT_OMNI */

struct	tcp_stream_request_struct {
  int	send_buf_size;
  int	recv_buf_size;	/* how big does the client want it - the */
			/* receive socket buffer that is */ 
  int	receive_size;   /* how many bytes do we want to receive at one */
			/* time? */ 
  int	recv_alignment; /* what is the alignment of the receive */
			/* buffer? */ 
  int	recv_offset;    /* and at what offset from that alignment? */ 
  int	no_delay;       /* do we disable the nagle algorithm for send */
			/* coalescing? */ 
  int	measure_cpu;	/* does the client want server cpu utilization */
			/* measured? */ 
  float	cpu_rate;	/* do we know how fast the cpu is already? */ 
  int	test_length;	/* how long is the test?		*/
  int	so_rcvavoid;    /* do we want the remote to avoid copies on */
			/* receives? */ 
  int	so_sndavoid;    /* do we want the remote to avoid send copies? */
  int   dirty_count;    /* how many integers in the receive buffer */
			/* should be made dirty before calling recv? */  
  int   clean_count;    /* how many integers should be read from the */
			/* recv buffer before calling recv? */ 
  int   port;           /* the port to which the recv side should bind
			   to allow netperf to run through those evil
			   firewall things */
  int   ipfamily;       /* the address family of ipaddress */
};

struct	tcp_stream_response_struct {
  int	recv_buf_size;	/* how big does the client want it	*/
  int	receive_size;
  int	no_delay;
  int	measure_cpu;	/* does the client want server cpu	*/
  int	test_length;	/* how long is the test?		*/
  int	send_buf_size;
  int	data_port_number;	/* connect to me here	*/
  float	cpu_rate;		/* could we measure	*/
  int	so_rcvavoid;	/* could the remote avoid receive copies? */ 
  int	so_sndavoid;	/* could the remote avoid send copies? */
};

struct tcp_stream_results_struct {
  double         bytes_received;
  unsigned int	 recv_calls;	
  float	         elapsed_time;	/* how long the test ran */
  float	         cpu_util;	/* -1 if not measured */
  float	         serv_dem;	/* -1 if not measured */
  int            cpu_method;    /* how was cpu util measured? */
  int            num_cpus;      /* how many CPUs had the remote? */
  int            recv_buf_size; /* how large was it at the end? */
  int            send_buf_size; /* how large was it at the end? */
};

struct	tcp_maerts_request_struct {
  int	send_buf_size;
  int	recv_buf_size;	/* how big does the client want it - the */
			/* receive socket buffer that is */ 
  int	send_size;      /* how many bytes do we want netserver to send
			   at one time? */
  int	send_alignment; /* what is the alignment of the send */
			/* buffer? */ 
  int	send_offset;    /* and at what offset from that alignment? */ 
  int	no_delay;       /* do we disable the nagle algorithm for send */
			/* coalescing? */ 
  int	measure_cpu;	/* does the client want server cpu utilization */
			/* measured? */ 
  float	cpu_rate;	/* do we know how fast the cpu is already? */ 
  int	test_length;	/* how long is the test?		*/
  int	so_rcvavoid;    /* do we want the remote to avoid copies on */
			/* receives? */ 
  int	so_sndavoid;    /* do we want the remote to avoid send copies? */
  int   dirty_count;    /* how many integers in the send buffer */
			/* should be made dirty before calling recv? */  
  int   clean_count;    /* how many integers should be read from the */
			/* recv buffer before calling recv? */ 
  int   port;           /* the port to which the recv side should bind
			   to allow netperf to run through those evil
			   firewall things */
  int   ipfamily;
};

struct	tcp_maerts_response_struct {
  int	recv_buf_size;	/* how big does the client want it	*/
  int	send_size;
  int	no_delay;
  int	measure_cpu;	/* does the client want server cpu	*/
  int	test_length;	/* how long is the test?		*/
  int	send_buf_size;
  int	data_port_number;	/* connect to me here	*/
  float	cpu_rate;		/* could we measure	*/
  int	so_rcvavoid;	/* could the remote avoid receive copies? */ 
  int	so_sndavoid;	/* could the remote avoid send copies? */
};

struct tcp_maerts_results_struct {
  double         bytes_sent;
  unsigned int	 send_calls;	
  float	         elapsed_time;	/* how long the test ran */
  float	         cpu_util;	/* -1 if not measured */
  float	         serv_dem;	/* -1 if not measured */
  int            cpu_method;    /* how was cpu util measured? */
  int            num_cpus;      /* how many CPUs had the remote? */
};

struct	tcp_rr_request_struct {
  int	recv_buf_size;	/* how big does the client want it	*/
  int	send_buf_size;
  int	recv_alignment;
  int	recv_offset;
  int	send_alignment;
  int	send_offset;
  int	request_size;
  int	response_size;
  int	no_delay;
  int	measure_cpu;	/* does the client want server cpu	*/
  float	cpu_rate;	/* do we know how fast the cpu is?	*/
  int	test_length;	/* how long is the test?		*/
  int	so_rcvavoid;    /* do we want the remote to avoid receive */
			/* copies? */ 
  int	so_sndavoid;    /* do we want the remote to avoid send copies? */
  int   port;           /* the port to which the recv side should bind
			   to allow netperf to run through those evil
			   firewall things */
  int   ipfamily;
};

struct	tcp_rr_response_struct {
  int	recv_buf_size;	/* how big does the client want it	*/
  int	no_delay;
  int	measure_cpu;	/* does the client want server cpu	*/
  int	test_length;	/* how long is the test?		*/
  int	send_buf_size;
  int	data_port_number;	/* connect to me here	*/
  float	cpu_rate;		/* could we measure	*/
  int	so_rcvavoid;	/* could the remote avoid receive copies? */
  int	so_sndavoid;	/* could the remote avoid send copies? */
};

struct tcp_rr_results_struct {
  unsigned int  bytes_received;	/* ignored initially */
  unsigned int	recv_calls;	/* ignored initially */
  unsigned int	trans_received;	/* not ignored  */
  float	        elapsed_time;	/* how long the test ran */
  float	        cpu_util;	/* -1 if not measured */
  float	        serv_dem;	/* -1 if not measured */
  int           cpu_method;    /* how was cpu util measured? */
  int           num_cpus;      /* how many CPUs had the remote? */
};

struct	tcp_conn_rr_request_struct {
  int	recv_buf_size;	/* how big does the client want it	*/
  int	send_buf_size;
  int	recv_alignment;
  int	recv_offset;
  int	send_alignment;
  int	send_offset;
  int	request_size;
  int	response_size;
  int	no_delay;
  int	measure_cpu;	/* does the client want server cpu	*/
  float	cpu_rate;	/* do we know how fast the cpu is?	*/
  int	test_length;	/* how long is the test?		*/
  int	so_rcvavoid;    /* do we want the remote to avoid receive */
			/* copies? */ 
  int	so_sndavoid;    /* do we want the remote to avoid send copies? */
  int   port;           /* the port to which the recv side should bind
			   to allow netperf to run through those evil
			   firewall things */
  int   ipfamily;
};


struct	tcp_conn_rr_response_struct {
  int	recv_buf_size;	/* how big does the client want it	*/
  int	no_delay;
  int	measure_cpu;	/* does the client want server cpu	*/
  int	test_length;	/* how long is the test?		*/
  int	send_buf_size;
  int	data_port_number;	/* connect to me here	*/
  float	cpu_rate;		/* could we measure	*/
  int	so_rcvavoid;	/* could the remote avoid receive copies? */
  int	so_sndavoid;	/* could the remote avoid send copies? */
};

struct tcp_conn_rr_results_struct {
  unsigned int	bytes_received;	/* ignored initially */
  unsigned int	recv_calls;	/* ignored initially */
  unsigned int	trans_received;	/* not ignored  */
  float	        elapsed_time;	/* how long the test ran */
  float	        cpu_util;	/* -1 if not measured */
  float	        serv_dem;	/* -1 if not measured */
  int           cpu_method;    /* how was cpu util measured? */
  int           num_cpus;      /* how many CPUs had the remote? */
};

struct	tcp_tran_rr_request_struct {
  int	recv_buf_size;	/* how big does the client want it	*/
  int	send_buf_size;
  int	recv_alignment;
  int	recv_offset;
  int	send_alignment;
  int	send_offset;
  int	request_size;
  int	response_size;
  int	no_delay;
  int	measure_cpu;	/* does the client want server cpu	*/
  float	cpu_rate;	/* do we know how fast the cpu is?	*/
  int	test_length;	/* how long is the test?		*/
  int	so_rcvavoid;    /* do we want the remote to avoid receive */
			/* copies? */ 
  int	so_sndavoid;    /* do we want the remote to avoid send copies? */
  int   port;           /* the port to which the recv side should bind
			   to allow netperf to run through those evil
			   firewall things */
  int   ipfamily;
};


struct	tcp_tran_rr_response_struct {
  int	recv_buf_size;	/* how big does the client want it	*/
  int	no_delay;
  int	measure_cpu;	/* does the client want server cpu	*/
  int	test_length;	/* how long is the test?		*/
  int	send_buf_size;
  int	data_port_number;	/* connect to me here	*/
  float	cpu_rate;		/* could we measure	*/
  int	so_rcvavoid;	/* could the remote avoid receive copies? */
  int	so_sndavoid;	/* could the remote avoid send copies? */
};

struct tcp_tran_rr_results_struct {
  unsigned int	bytes_received;	/* ignored initially */
  unsigned int	recv_calls;	/* ignored initially */
  unsigned int	trans_received;	/* not ignored  */
  float	        elapsed_time;	/* how long the test ran */
  float	        cpu_util;	/* -1 if not measured */
  float	        serv_dem;	/* -1 if not measured */
  int           cpu_method;    /* how was cpu util measured? */
  int           num_cpus;      /* how many CPUs had the remote? */

};

struct	udp_stream_request_struct {
  int	recv_buf_size;
  int	message_size;
  int   recv_connected;
  int	recv_alignment;
  int	recv_offset;
  int	checksum_off;
  int	measure_cpu;
  float	cpu_rate;
  int	test_length;
  int	so_rcvavoid;    /* do we want the remote to avoid receive */
			/* copies? */ 
  int	so_sndavoid;    /* do we want the remote to avoid send copies? */
  int   port;           /* the port to which the recv side should bind
			   to allow netperf to run through those evil
			   firewall things */
  int   ipfamily;
  
};

struct	udp_stream_response_struct {
  int	recv_buf_size;
  int	send_buf_size;
  int	measure_cpu;
  int	test_length;
  int	data_port_number;
  float	cpu_rate;
  int	so_rcvavoid;	/* could the remote avoid receive copies? */
  int	so_sndavoid;	/* could the remote avoid send copies? */
};

struct	udp_stream_results_struct {
  unsigned int	messages_recvd;
  unsigned int	bytes_received;
  float	        elapsed_time;
  float	        cpu_util;
  int           cpu_method;    /* how was cpu util measured? */
  int           num_cpus;      /* how many CPUs had the remote? */
};


struct	udp_rr_request_struct {
  int	recv_buf_size;	/* how big does the client want it	*/
  int	send_buf_size;
  int	recv_alignment;
  int	recv_offset;
  int	send_alignment;
  int	send_offset;
  int	request_size;
  int	response_size;
  int	no_delay;
  int	measure_cpu;	/* does the client want server cpu	*/
  float	cpu_rate;	/* do we know how fast the cpu is?	*/
  int	test_length;	/* how long is the test?		*/
  int	so_rcvavoid;    /* do we want the remote to avoid receive */
			/* copies? */ 
  int	so_sndavoid;    /* do we want the remote to avoid send copies? */
  int   port;           /* the port to which the recv side should bind
			   to allow netperf to run through those evil
			   firewall things */
  int   ipfamily;
};

struct	udp_rr_response_struct {
  int	recv_buf_size;	/* how big does the client want it	*/
  int	no_delay;
  int	measure_cpu;	/* does the client want server cpu	*/
  int	test_length;	/* how long is the test?		*/
  int	send_buf_size;
  int	data_port_number;	/* connect to me here	*/
  float	cpu_rate;		/* could we measure	*/
  int	so_rcvavoid;	/* could the remote avoid receive copies? */
  int	so_sndavoid;	/* could the remote avoid send copies? */
};

struct udp_rr_results_struct {
  unsigned int	bytes_received;	/* ignored initially */
  unsigned int	recv_calls;	/* ignored initially */
  unsigned int	trans_received;	/* not ignored  */
  float	        elapsed_time;	/* how long the test ran */
  float	        cpu_util;	/* -1 if not measured */
  float	        serv_dem;	/* -1 if not measured */
  int           cpu_method;    /* how was cpu util measured? */
  int           num_cpus;      /* how many CPUs had the remote? */
};

struct	tcp_cc_request_struct {
  int	recv_buf_size;	/* how big does the client want it	*/
  int	send_buf_size;
  int	recv_alignment;
  int	recv_offset;
  int	send_alignment;
  int	send_offset;
  int	request_size;
  int	response_size;
  int	no_delay;
  int	measure_cpu;	/* does the client want server cpu	*/
  float	cpu_rate;	/* do we know how fast the cpu is?	*/
  int	test_length;	/* how long is the test?		*/
  int	so_rcvavoid;    /* do we want the remote to avoid receive */
			/* copies? */ 
  int	so_sndavoid;    /* do we want the remote to avoid send copies? */
  int   port;           /* the port to which the recv side should bind
			   to allow netperf to run through those evil
			   firewall things */
  int   ipfamily;
};


struct	tcp_cc_response_struct {
  int	recv_buf_size;	/* how big does the client want it	*/
  int	no_delay;
  int	measure_cpu;	/* does the client want server cpu	*/
  int	test_length;	/* how long is the test?		*/
  int	send_buf_size;
  int	data_port_number;	/* connect to me here	*/
  float	cpu_rate;		/* could we measure	*/
  int	so_rcvavoid;	/* could the remote avoid receive copies? */
  int	so_sndavoid;	/* could the remote avoid send copies? */
};

struct tcp_cc_results_struct {
  unsigned int	bytes_received;	/* ignored initially */
  unsigned int	recv_calls;	/* ignored initially */
  unsigned int	trans_received;	/* not ignored  */
  float	        elapsed_time;	/* how long the test ran */
  float	        cpu_util;	/* -1 if not measured */
  float	        serv_dem;	/* -1 if not measured */
  int           cpu_method;    /* how was cpu util measured? */
  int           num_cpus;      /* how many CPUs had the remote? */
};

extern int
  rss_size_req,     /* requested remote socket send buffer size */
  rsr_size_req,     /* requested remote socket recv buffer size */
  rss_size,         /* remote socket send buffer size       */
  rsr_size,         /* remote socket recv buffer size       */
  rsr_size_end,
  rss_size_end,
  lss_size_req,     /* requested local socket send buffer size */
  lsr_size_req,     /* requested local socket recv buffer size */
  lss_size,         /* local  socket send buffer size       */
  lsr_size,         /* local  socket recv buffer size       */
  lss_size_end,
  lsr_size_end,
  req_size,         /* request size                         */
  rsp_size,         /* response size                        */
  send_size,        /* how big are individual sends         */
  recv_size,        /* how big are individual receives      */
  loc_nodelay,          /* don't/do use NODELAY locally         */
  rem_nodelay,          /* don't/do use NODELAY remotely        */
  loc_sndavoid,         /* avoid send copies locally            */
  loc_rcvavoid,         /* avoid recv copies locally            */
  rem_sndavoid,         /* avoid send copies remotely           */
  rem_rcvavoid;         /* avoid recv_copies remotely           */


extern void scan_sockets_args(int argc, char *argv[]);
extern struct addrinfo *complete_addrinfo(char *controlhost, 
				   char *data_address, 
				   char *port, 
				   int family, 
				   int type, 
				   int protocol, 
				   int flags);
extern void complete_addrinfos(struct addrinfo **remote,
			       struct addrinfo **local, 
			       char remote_host[], 
			       int type, 
			       int protocol, 
			       int flags);
extern int af_to_nf(int af);
extern int nf_to_af(int nf);
extern int nst_to_hst(int nst);
extern int hst_to_nst(int hst);
extern char *hst_to_str(int hst);
extern char *protocol_to_str(int protocol);
extern void print_top_test_header(char test_name[], 
				  struct addrinfo *source, 
				  struct addrinfo *destination);
extern void set_port_number(struct addrinfo *res, 
			    unsigned short port);
extern void set_hostname_and_port(char *hostname, 
				  char *portstr, 
				  int family, 
				  int port);
extern void set_sockaddr_family_addr_port(struct sockaddr_storage *sockaddr,
					  int family,
					  void *addr,
					  int port);
extern int  get_sockaddr_family_addr_port(struct sockaddr_storage *sockaddr,
					  int family,
					  void *addr,
					  int *port);
extern void send_tcp_stream(char remote_host[]);
extern void send_tcp_maerts(char remote_host[]);
extern void send_tcp_rr(char remote_host[]);
extern void send_tcp_conn_rr(char remote_host[]);
extern void send_tcp_cc(char remote_host[]);
extern void send_udp_stream(char remote_host[]);
extern void send_udp_rr(char remote_host[]);

extern void recv_tcp_stream();
extern void recv_tcp_maerts();
extern void recv_tcp_rr();
extern void recv_tcp_conn_rr();
extern void recv_tcp_cc();
extern void recv_udp_stream();
extern void recv_udp_rr();

extern void loc_cpu_rate();
extern void rem_cpu_rate();

#ifdef HAVE_ICSC_EXS
extern void send_exs_tcp_stream(char remotehost[]);
#endif /* HAVE_ICSC_EXS */

#ifdef HAVE_SENDFILE
extern void sendfile_tcp_stream(char remotehost[]);
#endif /* HAVE_SENDFILE */

#if !defined(HAVE_STRUCT_SOCKADDR_STORAGE) && !defined(sockaddr_storage)
#define sockaddr_storage sockaddr_in
#endif

#ifdef DO_NBRR
extern void send_tcp_nbrr(char remote_host[]);

extern void recv_tcp_nbrr();
#endif

