#include "semafor.h"

sembuf take_semafor_producer[2] =
{
    { SE, P, SEM_UNDO },
    { SB, P, SEM_UNDO }
};

sembuf free_semafor_producer[2] =
{
    { SB, V, SEM_UNDO },
    { SF, V, SEM_UNDO },
};

sembuf take_semafor_consumer[2] =
{
    { SF, P, SEM_UNDO },
    { SB, P, SEM_UNDO }
};

sembuf free_semafor_consumer[2] =
{
    { SB, V, SEM_UNDO },
    { SE, V, SEM_UNDO }
};
