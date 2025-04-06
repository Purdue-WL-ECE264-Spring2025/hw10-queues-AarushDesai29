#include "queue.h"
#include "tile_game.h"
#include <stdlib.h>

void enqueue(struct queue *q, struct game_state state) 
{
    size_t value = serialize(state);
    insert_at_tail(&(q -> data), value);
}

struct game_state dequeue(struct queue *q) 
{
    if (q -> data.head == NULL)
    {
        return (struct game_state){0};
    }
    uint64_t value = remove_from_head(&(q -> data));
    struct game_state state = deserialize(value);

    return state;

}
  

int number_of_moves(struct game_state start) 
{
    struct game_state solved =  {.tiles = {{1,2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, }},  .empty_row = 3, .empty_col = 3, .num_steps = 0};
    struct queue * queue = malloc(sizeof(struct queue));

    queue -> data.head = NULL;
    enqueue(queue, start);
    while ((queue) -> data.head != NULL)
    {
        struct game_state state = dequeue(queue);
        int equal = 1;
        //if (state.empty_row == 3 && state.empty_col == 3)
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (state.tiles[i][j] != solved.tiles[i][j])
                {
                    equal = 0;
                }
            }
        }
        if (equal == 1)
        {
            return state.num_steps;
        }
        struct game_state state_up = state;
        move_up(&state_up);
        int check1 = 0;
        size_t serial_up = serialize(state_up);

        struct game_state state_left = state;
        move_left(&state_left);
        int check2 = 0;
        size_t serial_left = serialize(state_left);

        struct game_state state_down = state;
        move_down(&state_down);
        int check3 = 0;
        size_t serial_down = serialize(state_down);

        struct game_state state_right = state;
        move_right(&state_right);
        int check4 = 0;
        size_t serial_right = serialize(state_right);

        struct list_node * curr = queue -> data.head;
        if (curr == NULL)
        {
            enqueue(queue, state_up);
            enqueue(queue, state_left);
            enqueue(queue, state_down);
            enqueue(queue, state_right);
        }
        else
        {
            while (curr -> next != NULL)
            {
                if (curr -> value == serial_up)
                {
                    check1 = 1;
                }   

                if (curr -> value == serial_left)
                {
                    check2 = 1;
                }

                if (curr -> value == serial_down)
                {
                    check3 = 1;
                }

                if (curr -> value == serial_right)
                {
                    check4 = 1;
                }
                curr = curr -> next;
            }
            if (check1 == 0)
            {
                enqueue(queue, state_up);
            }
            if (check2 == 0)
            {
                enqueue(queue, state_left);
            }
            if (check3 == 0)
            {
                enqueue(queue, state_down);
            }
            if (check4 == 0)
            {
                enqueue(queue, state_right);
            }
        }
    }
    return 0; 
}
