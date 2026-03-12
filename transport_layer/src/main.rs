mod connection;
mod retransmission;
mod state_machine;

use connection::TcpConnection;

fn main()
{
  let mut conn = TcpConnection::new();
  
  connection::send_syn(&mut conn);
  
  loop
  {
    retransmission::check_retransmission(&mut conn);
    
    std::thread::sleep(std::time::Duration::from_millis(100));
  }
}
