#define t_queue_elem int

typedef struct queue queue;

queue* queue_new (int maxsize);

void queue_free (queue* q);

int queue_getsize (queue* q);

int queue_getmaxsize (queue* q);

int queue_isfull (queue* q);

int queue_isempty (queue* q);

void enqueue (queue* q, t_queue_elem elem);

t_queue_elem dequeue (queue* q);

t_queue_elem peek (queue* q);

void queue_add_random(queue* q, int cant_elem);

void queue_print(queue* q);

int queue_sum_elements(queue* q);

void queue_invert(queue* q);

queue* queue_copy(queue* q);

