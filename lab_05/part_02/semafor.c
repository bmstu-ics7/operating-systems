#include "semafor.h"

sembuf take_semafor_writer[4] =
{
    { WAIT_WRITERS,  INC, SEM_UNDO },
    { READERS_COUNT, ZER, SEM_UNDO },
    { ACTIVE_WRITER, DEC, SEM_UNDO },
    { WAIT_WRITERS,  DEC, SEM_UNDO }
};

sembuf free_semafor_writer[1] =
{
    { ACTIVE_WRITER, INC, SEM_UNDO }
};

sembuf take_semafor_reader[5] =
{
    { WAIT_READERS,  INC, SEM_UNDO },
    { ACTIVE_WRITER, ZER, SEM_UNDO },
    { WAIT_WRITERS,  ZER, SEM_UNDO },
    { READERS_COUNT, INC, SEM_UNDO },
    { WAIT_READERS,  DEC, SEM_UNDO }
};

sembuf free_semafor_reader[1] =
{
    { READERS_COUNT, DEC, SEM_UNDO }
};
