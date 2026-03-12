use crate::connection::{TcpConnection,TcpState};

pub fn process_packet(conn: &mut TcpConnection, syn:bool, ack: bool, seq: u32, ack_num: u32)
{
  match conn.state
  {
    TcpState::SynSent => 
    {
      if syn && ack
      {
        println!("Received SYN-ACK");
        
        crate::connection::handle_syn_ack(conn,seq,ack_num);
      }
    }
    _ => {}
  }
}
