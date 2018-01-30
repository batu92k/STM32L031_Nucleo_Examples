# STM32L031 Nucleo Kiti için Örnek KEIL Projeleri

### Hakkında

- Bu repository, STM32L031 Nucleo kiti için tasarlanmış örnek uygulamalar içermektedir.
- Projeler içerisindeki uygulamalarda HAL (Hardware Abstraction Layer) kütüphaneleri yerine LL (Low Level) kütüphaneler kullanımıştır.

### Örnek Projeler

 - #### LED_BLINK
   - Standart LED yak-söndür uygulaması
 - #### USART_TX
   - Mikrodenetleyiciden PC'ye PL2303 TTL çevirici ile USART üzerinden periyodik veri gönderimi
 - #### USART_TX_RX
   - Eş zamanlı olarak mikrodenetleyiciden USART ile PC'ye veri gönderimi ve USART RX not empty kesmesi ile PC'den gelen karakterin yakalanması ve değerlendirilmesi 
 - #### DES_TEST
   - DES (Data Encryption Standart) kripto algoritmasının Nucleo kiti üzerinde çalıştırılarak, örnek bir dizinin kriptolanması, kirpto çözümü ve sonuçların USART üzerinden HEX formatında PC'ye gönderilmesi. USART RX not empty kesmesi ile PC'den gelen karakterin yakalanması ve değerlendirilmesi 
      
# Example KEIL Projects for STM32L031 Nucleo Board

### About

- This repository includes example KEIL projects for STM32L031 Nucleo board
- Low Level Drivers (LL) is used in the applications of this repository, instead of HAL (Hardware Abstraction Layer) Drivers

### Exapmle Projects

 - #### LED_BLINK
   - Standard LED toggle application
 - #### USART_TX
   - Periodic data transmission from microprocessor to PC through USART communication with PL2303 TTL converter
 - #### USART_TX_RX
   - Simultaneously data transmission from microprocessor to PC through USART communication and catching the characters that are sent from PC with RX not empty interrupt routine
 - #### DES_TEST
   - The project includes, DES (Data Encryption Standart) algorithm implementation on Nucleo board. It contains encryption and decryption routines of an array, transmitting routine of plain and ciphered arrays as HEX characters. Same time It can receive the characters that send from PC with RX not empty interrupt

