# Networking
## HTTP
- you want to order something, go to `mall`, look for right `store`, you order `food`, order `drink` => `mall:store/food` || `mall:store/drink`
- you want to order something, go to `ip`, look for right `port`, you order `/food`, order `/drink` => `ip:port/food` || `ip:port/drink`
- `ip` tell which machine, `port` tell which program on that machine serving you, single program serving multiple services
## Socket
- is abstraction, an illusion communicating through network same as operating on file, `talk/listen` == `send/receive` == `write/read`,
- include (src `ip/port` && des `ip/port`) infor, one `socket` -> one `port`,
- one `port` <- many `socket`, obviously because single port `80` allow trillions connections, so there would be one socket each connection for port `80`, differ only in `des` infor
- analogy: power strip, one wall outlet (port) supports multiple electrical devices (sockets). 
- 



































