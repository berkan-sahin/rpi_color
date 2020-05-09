sensör i2c adres: 0x29

önce command register a istenen adres yazılacak
sonra okunacak

0x14 :clear low
0x15 :clear hi
0x16 :red low
0x17 :red hi
0x18 :green lo
0x19 :green hi
0x1A :blue lo
0x1B :blue hi



okuma rutini:
- 0b10010100  : command seç, otomatik arttır, clear low dan başla
- uint16 clear
  uint16 red
  uint16 green
  uint16 blue


0x00 enable register
- 0b00000011 yazarsak sistem gücü + RGBC açık

0x01 ATIME 
- 0x00 yaparsak 256 saykıl, 700ms, max. hassaslık

0x0F Control
- 0x00 min. kazanç

0x12 id
- 0x44 okunacak

0x13: status
0.bit setli ise rgbc okunabilir demektir

