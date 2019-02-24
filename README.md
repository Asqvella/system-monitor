# Sysmon
## Monitoring and alert system
### Features
* Memory monitoring  
* Real time graphs  
* Email alert   
### Setup  
Clone from github  
` $ git clone https://github.com/Asqvella/system-monitor `  
Install sqlite library  
` $ sudo apt-get install sqlite3 libsqlite3-dev `  
Install curl library  
` $ sudo apt-get install libcurl4-openssl-dev `  
Fill the fields in metrics.c for alerting  
`max_value, URL, USERPWD, POSTFIELDS`  
Compile this  
` $ make `  


