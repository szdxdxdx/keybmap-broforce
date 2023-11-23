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

/* util enum val with str name */
#define enum_str_0(e)                                   #e,
#define enum_str_1(e)                                   enum_str_0(e) enum_str_2
#define enum_str_1_end
#define enum_str_2(e)                                   enum_str_0(e) enum_str_1
#define enum_str_2_end
#define enum_str(enums)                                 strcat2(enum_str_1 enums, _end)

#define enum_val_0(e)                                   e,
#define enum_val_1(e)                                   enum_val_0(e) enum_val_2
#define enum_val_1_end
#define enum_val_2(e)                                   enum_val_0(e) enum_val_1
#define enum_val_2_end
#define enum_val(enums)                                 strcat2(enum_val_1 enums, _end)

#define enum_to_str(enum_name, e)                       enum_name##_str[e]
#define def_enum_with_str_name(enum_name, enums)        typedef enum { enum_val(enums) } enum_name; const char *enum_name##_str[] = { enum_str(enums) };

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
                                                        }                                                           \

#if 0

/* 宏函数介绍 
   Introduction to macro functions */
void main(void)
{
    /* 声明枚举和对应的字符串列表（要求枚举只能从零开始自增，不能自定义枚举的值）
       Declare enums and corresponding string array (cannot customize the values of enums) */
    def_enum_with_str_name(number, (zero)(one)(two)(three));
    printf("%s = %d\n", enum_to_str(number, zero), zero);
    printf("%s = %d\n", enum_to_str(number, one), one);
    printf("%s = %d\n", enum_to_str(number, two), two);
    printf("%s = %d\n", enum_to_str(number, three), three);

    for (;;)
    {
        /* 监听A、B、C、D、E键的状态
           update the status of A, B, C, D, E keys in loop */
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

void four_players(void)
{
    puts(
        " +---------------------------[4 players]---------------------------+\n"
        " |           |                                                     |\n"
        " |           |       - - --+------------[game setting]-------------+\n"
        " | key       | description | player1 | player2 | player3 | player4 |\n"
        " +-----------+-------------+---------+---------+---------+---------+\n"
        " | numpad8   | up          | numpad8 | W       | I       | 1       |\n"
        " | numpad4   | left        | numpad4 | A       | J       | 2       |\n"
        " | numpad5   | down        | numpad5 | S       | K       | 3       |\n"
        " | numpad6   | right       | numpad6 | D       | L       | 4       |\n"
        " | Z         | shoot       | G       | E       | Y       | 8       |\n"
        " | X         | skill       | X       | R       | U       | 5       |\n"
        " | C         | melee       | C       | T       | O       | 6       |\n"
        " | V         | pose        | V       | Q       | P       | 7       |\n"
        " |           |       - - --+---------+---------+---------+---------+\n"
        " | SPACE     | change shooting_mode                                |\n"
        " | UP        | change quick_shooting_time_interval                 |\n"
        " | DOWN      | change quick_shooting_time_interval                 |\n"
        " | SPACE + X | select keybmap mode                                 |\n"
        " +-----------+-----------------------------------------------------+"
    );

    def_enum_with_str_name(enum_shooting_mode, (normal)(quick));
    static enum_shooting_mode shooting_mode = normal;

    static time_t quick_shooting_time_interval = 30;

    printf("shooting_mode = %s\n", enum_to_str(enum_shooting_mode, normal));
    printf("quick_shooting_time_interval = %lld\n",
        quick_shooting_time_interval
    );

    for (;;)
    {
        update_key_status(
            (VK_NUMPAD8)(VK_NUMPAD4)(VK_NUMPAD5)(VK_NUMPAD6)('Z')('X')('C')('V')
            (VK_SPACE)(VK_UP)(VK_DOWN)
        );

        sync_key_status(VK_NUMPAD8, ('W')('I')('1'));
        sync_key_status(VK_NUMPAD4, ('A')('J')('2'));
        sync_key_status(VK_NUMPAD5, ('S')('K')('3'));
        sync_key_status(VK_NUMPAD6, ('D')('L')('4'));
        sync_key_status('X',        ('R')('U')('5'));
        sync_key_status('C',        ('T')('O')('6'));
        sync_key_status('V',        ('Q')('P')('7'));

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

        if (is_key_up_to_down(VK_SPACE))
        {
            shooting_mode = (normal == shooting_mode) ? quick : normal;
            printf("shooting_mode = %s\n", enum_to_str(enum_shooting_mode, shooting_mode));
        }
        else if (is_key_up_to_down(VK_UP))
        {
            if ((quick_shooting_time_interval += 2) > 70) {
                quick_shooting_time_interval = 30;
            }
            printf("quick_shooting_time_interval = %lld\n",
                quick_shooting_time_interval
            );
        }
        else if (is_key_up_to_down(VK_DOWN))
        {
            if ((quick_shooting_time_interval -= 2) < 30) {
                quick_shooting_time_interval = 70;
            }

            printf("quick_shooting_time_interval = %lld\n",
                quick_shooting_time_interval
            );
        }

        if (is_key_down(VK_SPACE) && is_key_up_to_down('X')) {
            break;
        }
    }

    return;
}

void one_player(void)
{
    puts(
        " +--------------------[1 player]-------------------+\n"
        " | key       | description | game setting          |\n"
        " +-----------+-------------+-----------------------+\n"
        " | numpad8   | up          | numpad8               |\n"
        " | numpad4   | left        | numpad4               |\n"
        " | numpad5   | down        | numpad5               |\n"
        " | numpad6   | right       | numpad6               |\n"
        " | Z         | shoot       | G                     |\n"
        " | X         | skill       | X                     |\n"
        " | C         | melee       | C                     |\n"
        " | V         | pose        | V                     |\n"
        " |           |       - - --+-----------------------+\n"
        " | SPACE     | change shooting_mode                |\n"
        " | UP        | change quick_shooting_time_interval |\n"
        " | DOWN      | change quick_shooting_time_interval |\n"
        " | SPACE + X | select keybmap mode                 |\n"
        " +-----------+-------------------------------------+"
    );

    def_enum_with_str_name(enum_shooting_mode, (normal)(quick));
    enum_shooting_mode shooting_mode = normal;

    time_t quick_shooting_time_interval = 30;

    printf("shooting_mode = %s\n", enum_to_str(enum_shooting_mode, normal));
    printf("quick_shooting_time_interval = %lld\n",
        quick_shooting_time_interval
    );

    for (;;)
    {
        update_key_status(('Z')('X')(VK_SPACE)(VK_UP)(VK_DOWN));

        switch (shooting_mode)
        {
        case normal:
        {
            sync_key_status('Z', ('G'));
            break;
        }
        case quick:
        {
            if (is_key_down('Z'))
            {
                static_timer(quick_shooting_time_interval)
                {
                    send_event_to_key(
                        (key_event_up_to_down, 'G')
                        (key_event_down_to_up, 'G')
                    );
                }
            }
            break;
        }
        }

        if (is_key_up_to_down(VK_SPACE))
        {
            shooting_mode = (normal == shooting_mode) ? quick : normal;
            printf("shooting_mode = %s\n", enum_to_str(enum_shooting_mode, shooting_mode));
        }
        else if (is_key_up_to_down(VK_UP))
        {
            if ((quick_shooting_time_interval += 2) > 70) {
                quick_shooting_time_interval = 30;
            }
            printf("quick_shooting_time_interval = %lld\n",
                quick_shooting_time_interval
            );
        }
        else if (is_key_up_to_down(VK_DOWN))
        {
            if ((quick_shooting_time_interval -= 2) < 30) {
                quick_shooting_time_interval = 70;
            }

            printf("quick_shooting_time_interval = %lld\n",
                quick_shooting_time_interval
            );
        }

        if (is_key_down(VK_SPACE) && is_key_up_to_down('X')) {
            break;
        }
    }

    return;
}

int main(void)
{
    puts("\n keybmap broforce, version: " __DATE__ " " __TIME__ "\n");

    struct {
        const char *name;
        void (*func)(void);
    } mode[] =
    {
        {
            .name = "4 players",
            .func = four_players
        }, {
            .name = "1 player",
            .func = one_player
        },
    };
    size_t idx = 0;
    size_t size = ARRAYSIZE(mode);

loop:
    puts(
        " +--------[ select keybmap mode]--------+\n"
        " | key       | description              |\n"
        " +-----------+--------------------------+\n"
        " | UP        | switch keybmap mode      |\n"
        " | DOWN      | switch keybmap mode      |\n"
        " | Z         | select this mode         |\n"
        " | SPACE + X | exit                     |\n"
        " +-----------+--------------------------+"
    );
    printf("mode = %s\n", mode[idx].name);

    for (;;)
    {
        update_key_status((VK_UP)(VK_DOWN)('Z')('X')(VK_SPACE));

        if (is_key_up_to_down(VK_UP))
        {
            idx = (idx + 1) % size;
            printf("mode = %s\n", mode[idx].name);
        }
        else if (is_key_up_to_down(VK_DOWN)) {
            idx = (idx - 1) % size;
            printf("mode = %s\n", mode[idx].name);
        }
        else if (is_key_up_to_down('Z'))
        {
            mode[idx].func();
            goto loop;
        }
        else if (is_key_down(VK_SPACE) && is_key_up_to_down('X'))
        {
            break;
        }
    }

    return 0;
}

#endif
