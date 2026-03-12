use std::time::Instant;

use crate::connection::TcpConnection;

pub fn check_retransmission(conn: &mut TcpConnection)
{
  if let Some(start) = conn.retrans_timer
  {
    if Instant::now().duration_since(start) > conn.rto 
   {
     println!("Retransmission timeout");
     
     retransmit_syn(conn);
     
     conn.retrans_timer = Some(Instant::now());
   }
  }
}

fn retransmit_syn(conn: &TcpConnection)
{
  println!("Retransmitting SYN seq={}",conn.snd_una);
}
