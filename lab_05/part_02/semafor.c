#include "semafor.h"

sembuf take_semafor_writer[2] =
{
    { READERS, ZER, SEM_UNDO },
    { WRITERS, DEC, SEM_UNDO }
};

sembuf free_semafor_writer[1] =
{
    { WRITERS, INC, SEM_UNDO }
};

sembuf take_semafor_reader[2] =
{
    { WRITERS, ZER, SEM_UNDO },
    { READERS, INC, SEM_UNDO }
};

sembuf free_semafor_reader[1] =
{
    { READERS, DEC, SEM_UNDO }
};
