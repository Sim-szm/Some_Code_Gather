    #include <stdlib.h>
    #include <stdio.h>

    typedef struct node
    {
        int data;
        struct node *next;
    } Node;

    typedef struct
    {
        Node *head;
        Node *tail;
        int length;
    } Looplink;

    Looplink *init_looplink()
    {
        Looplink *list = NULL;

        list = (Looplink *)malloc(sizeof(Looplink));
        if(NULL == list)
        {
            return NULL;
        }

        list->head = list->tail = NULL;
        list->length = 0;

        return list;
    }

    void looplink_append(Looplink *list, int value)
    {
        Node *node = NULL;

        if(NULL == list)
        {
            return;
        }

        node = (Node *)malloc(sizeof(Node));
        if(NULL == node)
        {
            return;
        }
        node->data = value;

        if(NULL != list->head)
        {
            node->next = list->head;
            list->tail->next = node;
            list->tail = node;
        }
        else
        {
            list->head = list->tail = node;
            node->next = node;
        }
        list->length++;
    }

    int resolve_joseph(Looplink *list_jose, int n_jose, int m_jose)
    {
        int i = 0;
        int result = 0;
        Node *ptr = NULL;
        Node *del = NULL;

        if(NULL == list_jose)
        {
            return -1;
        }
        
        while(i < n_jose)
        {
            looplink_append(list_jose,++i);
        }

        ptr = list_jose->head;

        while(0 < list_jose->length)
        {
            for(i=1; i<(m_jose-1); i++)
            {
                ptr = ptr->next;
            }

            del = ptr->next;
            ptr->next = del->next;
            ptr = ptr->next;
            if(1 == list_jose->length)
            {
                result = del->data;
            }

            free(del);
            list_jose->length--;
        }

        return result;
    }

    int main(int argc, char *argv[])
    {
        int n_jose = 0;
        int m_jose = 0;
        Looplink *list = NULL;

        list = init_looplink();
        if(NULL == list)
        {
            return -1;
        }

        printf("人数上限:");
        scanf("%d",&n_jose);
        printf("报数上限:");
        scanf("%d",&m_jose);
        printf("最后出列者:%d\n",resolve_joseph(list,n_jose,m_jose));

        free(list);

        return 0;
    }
