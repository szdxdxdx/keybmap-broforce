#include <stdio.h>
#include <time.h>
#include <Windows.h>

int key_status[256] = { 0 };

/* util strcat */
#define strcat1(x, y)                                   x ## y
#define strcat2(x, y)                                   strcat1(x, y)

/* util timer */
#define static_timer(time_interval)                     static time_t strcat2(timer, __LINE__) = 0; \
                                                        if ((strcat2(timer, __LINE__) + time_interval <= clock()) ? (strcat2(timer, __LINE__) = clock()) : 0)

/* update_key_status */
#define update_key_status_0(key)                        key_status[key] = (((key_status[key] << 1) | !!GetAsyncKeyState(key))) & 0b011;
#define update_key_status_1(key)                        update_key_status_0(key) update_key_status_2
#define update_key_status_1_end
#define update_key_status_2(key)                        update_key_status_0(key) update_key_status_1
#define update_key_status_2_end
#define update_key_status(keys)                         strcat2(update_key_status_1 keys, _end)

/* get_key_status */
#define get_key_status(key)                             (key_status[key])
#define is_key_up_to_down(key)                          (get_key_status(key) == 0b001)
#define is_key_down_to_up(key)                          (get_key_status(key) == 0b010)
#define is_key_up(key)                                  ( ! get_key_status(key))
#define is_key_down(key)                                get_key_status(key)

/* send_event_to_key */
#define key_event_up_to_down                            0
#define key_event_down_to_up                            KEYEVENTF_KEYUP
#define send_event_to_key_0(key_event, key)             keybd_event(key, 0, key_event, 0);
#define send_event_to_key_1(key_event, key)             send_event_to_key_0(key_event, key) send_event_to_key_2
#define send_event_to_key_2_end
#define send_event_to_key_2(key_event, key)             send_event_to_key_0(key_event, key) send_event_to_key_1
#define send_event_to_key_1_end
#define send_event_to_key(event_and_key_pair)           strcat2(send_event_to_key_1 event_and_key_pair, _end)

#define send_key_event_up_to_down_to_keys_0(key)        send_event_to_key_0(key_event_up_to_down, key)
#define send_key_event_up_to_down_to_keys_1(key)        send_event_to_key_0(key_event_up_to_down, key) send_key_event_up_to_down_to_keys_2
#define send_key_event_up_to_down_to_keys_2_end
#define send_key_event_up_to_down_to_keys_2(key)        send_event_to_key_0(key_event_up_to_down, key) send_key_event_up_to_down_to_keys_1
#define send_key_event_up_to_down_to_keys_1_end

#define send_key_event_down_to_up_to_keys_0(key)        send_event_to_key_0(key_event_down_to_up, key)
#define send_key_event_down_to_up_to_keys_1(key)        send_event_to_key_0(key_event_down_to_up, key) send_key_event_down_to_up_to_keys_2
#define send_key_event_down_to_up_to_keys_2_end
#define send_key_event_down_to_up_to_keys_2(key)        send_event_to_key_0(key_event_down_to_up, key) send_key_event_down_to_up_to_keys_1
#define send_key_event_down_to_up_to_keys_1_end

#define send_event_to_keys(key_event, keys)             strcat2(send_##key_event##_to_keys_1 keys, _end)

#define sync_key_status(src_key, dst_keys)              if (is_key_up_to_down(src_key)) {                           \
                                                            send_event_to_keys(key_event_up_to_down, dst_keys);     \
                                                        } else if (is_key_down_to_up(src_key)) {                    \
                                                            send_event_to_keys(key_event_down_to_up, dst_keys);     \
                                                        }

#if 1

/* 宏函数介绍 
   Introduction to macro functions */
void main(void)
{
    for (;;)
    {
        /* 监听A、B、C、D、E键的状态
           update the status of A, B, C, D, E keys in for loop */
        update_key_status( ('A')('B')('C')('D')('E') );

        if (is_key_up_to_down('A')) {
            puts("key_up_to_down: A");
        }
        else if (is_key_down_to_up('A')) {
            puts("key_down_to_up: A");
        }

        /* 按下B键的同时，模拟按下 ctrl + V
           While pressing the B key, simulate pressing ctrl + V */
        if (is_key_up_to_down('B'))
        {
            send_event_to_key(
                (key_event_up_to_down, VK_CONTROL)
                (key_event_up_to_down, 'V')
                (key_event_down_to_up, 'V')
                (key_event_down_to_up, VK_CONTROL)
            );
        }
        
        /* 按下C键的同时，模拟按下ctrl + V
           While pressing the C key, simulate pressing ctrl + V */
        if (is_key_down_to_up('C')) {
            send_event_to_keys(key_event_up_to_down, (VK_CONTROL)('V'));
            send_event_to_keys(key_event_down_to_up, ('V')(VK_CONTROL));
        }

        /* 将D键的状态（按下和松开两个瞬间态）同步到X、Y、Z键
           Synchronize the state of the D key (two instantaneous states of
           pressing and releasing) to the X, Y, and Z keys
        */
        sync_key_status('D', ('X')('Y')('Z'));
        
        /* 按住E键时，每500毫秒和每1000毫秒各做一次输出
           When pressing the E key, output will be made
           every 500 milliseconds and every 1000 milliseconds */
        if (is_key_down('E'))
        {
            static_timer(500) {
                puts("E 500");
            }

            static_timer(1000) {
                puts("E 1000");
            }
        }
    }
}

#else

/* keybmap_broforce */

int main(void)
{
    puts(
        "  keybmap_broforce, version: " __DATE__ " " __TIME__    "\n"
        "                                                         \n"
        " +----------------[ game key settings ]----------------+ \n"
        " | controll | player1      player2   player3   player4 | \n"
        " +----------+------------+---------+---------+---------+ \n"
        " | up       | VK_NUMPAD8   W         I         1       | \n"
        " | left     | VK_NUMPAD4   A         J         2       | \n"
        " | down     | VK_NUMPAD5   S         K         3       | \n"
        " | right    | VK_NUMPAD6   D         L         4       | \n"
        " | shoot    | G            E         Y         8       | \n"
        " | skill    | X            R         U         5       | \n"
        " | melee    | C            T         O         6       | \n"
        " | pose     | V            Q         P         7       | \n"
        " +----------+------------+---------+---------+---------+ \n"
        "                                                         \n"
        " +-------------------[ keybmap ]-----------------------+ \n"
        " | key        |   controll                             | \n"
        " +------------+----------------------------------------+ \n"
        " | VK_NUMPAD8 | up                                     | \n"
        " | VK_NUMPAD4 | left                                   | \n"
        " | VK_NUMPAD5 | down                                   | \n"
        " | VK_NUMPAD6 | right                                  | \n"
        " | G          | shoot                                  | \n"
        " | X          | skill                                  | \n"
        " | C          | melee                                  | \n"
        " | V          | pose                                   | \n"
        " | VK_SPACE   | change shooting_mode                   | \n"
        " | VK_UP      | change quick_shooting_time_interval    | \n"
        " | VK_ESCAPE  | quit                                   | \n"
        " +------------+----------------------------------------+ "
    );
    

    for (;;)
    {
        update_key_status(
            (VK_NUMPAD8)(VK_NUMPAD4)(VK_NUMPAD5)(VK_NUMPAD6)
            ('Z')('X')('C')('V')
            (VK_SPACE)(VK_ESCAPE)(VK_UP)
        );

        sync_key_status(VK_NUMPAD8, ('W')('I')('1'));
        sync_key_status(VK_NUMPAD4, ('A')('J')('2'));
        sync_key_status(VK_NUMPAD5, ('S')('K')('3'));
        sync_key_status(VK_NUMPAD6, ('D')('L')('4'));
        sync_key_status('X',        ('R')('U')('5'));
        sync_key_status('C',        ('T')('O')('6'));
        sync_key_status('V',        ('Q')('P')('7'));

        static enum { normal, quick } shooting_mode = normal;
        static int quick_shooting_time_interval = 50;
        switch (shooting_mode)
        {
        case normal:
        {
            sync_key_status('Z', ('G')('Y')('E')('8'));
            break;
        }
        case quick:
        {
            if (is_key_down('Z'))
            {
                static_timer(quick_shooting_time_interval) {
                    send_event_to_keys(key_event_up_to_down, ('G')('Y')('E')('8'));
                    send_event_to_keys(key_event_down_to_up, ('G')('Y')('E')('8'));
                }
            }
            break;
        }
        }

        if (is_key_up_to_down(VK_ESCAPE)) {
            break;
        }

        if (is_key_up_to_down(VK_SPACE)) {
            switch (shooting_mode)
            {
            case normal: {
                shooting_mode = quick;
                puts("shooting_mode = quick");
                break;
            }
            case quick: {
                shooting_mode = normal;
                puts("shooting_mode = normal");
                break;
            }
            }
        }

        if (is_key_up_to_down(VK_UP)) {
            quick_shooting_time_interval += 2;
            if (quick_shooting_time_interval > 80) {
                quick_shooting_time_interval = 40;
            }
            printf("quick_shooting_time_interval = %d\n", quick_shooting_time_interval);
        }
    }

    return 0;
}

#endif
