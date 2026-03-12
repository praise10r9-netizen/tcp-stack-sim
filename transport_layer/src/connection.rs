use std::time::{Instant, Duration};

pub enum TcpState
{
  Closed,
  SynSent,
  Established,
}

pub struct TcpConnection
{
  pub state: TcpState,
  
  pub snd_una: u32,
  pub snd_nxt: u32,
  
  pub rcv_nxt: u32,
  
  pub retrans_timer: Option<Instant>,
  
  pub rto: Duration,
}

impl TcpConnection
{
  pub fn new() -> Self 
  {
    TcpConnection
    {
      state: TcpState::Closed,
      
      snd_una: 0,
      snd_nxt: 0,
      
      rcv_nxt: 0,
      
      retrans_timer: None,
      
      rto: Duration::from_secs(1),
    }
  }
}

pub fn send_syn(conn: &mut TcpConnection)
{
  let initial_seq = 1000;
  conn.snd_una = initial_seq;
  conn.snd_nxt = initial_seq + 1;
  
  conn.retrans_timer = Some(Instant::now());
  
  conn.state = TcpState::SynSent;
  
  println!("Sending SYN seq={}",initial_seq);
  
}

pub fn handle_syn_ack(conn: &mut TcpConnection, seq: u32, ack: u32)
{
  if ack == conn.snd_nxt
  {
    conn.rcv_nxt = seq + 1;
    
    conn.snd_una = ack;
    
    conn.state = TcpState::Established;
    
    conn.retrans_timer = None;
    
    println!("Handshake completed");
  }else
  {
    println!("Unexpected ACK");
  }
} 
