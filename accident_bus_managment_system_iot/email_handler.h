// #ifndef EMAIL_HANDLER_H
// #define EMAIL_HANDLER_H


// #include <ESP32_MailClient.h>

// void setup_smtp_client(void);
// void send_test_email(void);
// void smtp_callback(SendStatus msg);

// #define DOMAIN "smtp-mail.outlook.com"
// #define DOMAIN_PORT 587
// #define SECURITY_PROTOCOL "TLS"
// #define SENDER_EMAIL_ADDRESS "suhail.altyif@outlook.com"
// #define SENDER_EMAIL_PASSWORD "leyjxwembxsdqerk"
// #define POLICE_RECEIVER_EMAIL_ADDRESS "nedalxzo@gmail.com"
// #define BUS_LINE_RECEIVER_EMAIL_ADDRESS "suhayl3483@gmail.com"
// #define POLICE 1
// #define BUS_LINE 2


// String TEST_EMAIL = "<h1>TEST EMAIL FROM ESP32-SYSTEM</h1>";
// String SYSTEM_START_EMAIL = "System Is On Now";

// uint8_t smtp_client_status = 0;

// SMTPData smtp_data;



// bool send_email(String email_msg, int email_id){

//   // Set the SMTP Server Email host, port, account and password
//   smtp_data.setLogin(DOMAIN, DOMAIN_PORT, SENDER_EMAIL_ADDRESS, SENDER_EMAIL_PASSWORD);

//   // Set the sender name and Email
//   smtp_data.setSender("Bus IoT System", SENDER_EMAIL_ADDRESS);

//   // Set Email priority or importance High, Normal, Low or 1 to 5 (1 is highest)
//   smtp_data.setPriority("High");

//   if (email_id == 1){
//     // Set the subject
//     smtp_data.setSubject("ESP32-SYSTEM-ALARM");
//   }else if (email_id == 2){
//     smtp_data.setSubject("ESP32-SYSTEM-ALARM");
//   }else{

//   }

//   // Set the message with HTML format
//   smtp_data.setMessage(email_msg, true);

//   // Add recipients
//   if (email_id == POLICE){
//     // Set the subject
//     smtp_data.addRecipient(POLICE_RECEIVER_EMAIL_ADDRESS);
//   }else if (email_id == BUS_LINE){
//     smtp_data.addRecipient(BUS_LINE_RECEIVER_EMAIL_ADDRESS);
//   }else{

//   }

//   smtp_data.setSendCallback(smtp_callback);

//   // Start sending Email, can be set callback function to track the status
//   if (!MailClient.sendMail(smtp_data)) {
//     Serial.println("Error sending Email, " + MailClient.smtpErrorReason());
//     smtp_client_status = 0;
//     return false;
//   }
//   smtp_client_status = 1;
//   // Clear all data from Email object to free memory
//   smtp_data.empty();
//   return true;
// }

// void smtp_callback(SendStatus msg){
  
//   Serial.println(msg.info());

//   if (msg.success()){
//     smtp_client_status = 1;
//   }
// }


// #endif