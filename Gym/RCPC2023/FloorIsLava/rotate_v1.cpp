    /* rotate the room (left side) */
    for (int i = 0; i < n; i++)
    {
        int offset = n - i - 1;
        for (int k = 0; k < offset; k++)
        {
            room_rot[i].push_back(0);
        }

        for (int j = 0; j < m; j++)
        {
            if (i - j < 0)
            {
                break;
            }
            room_rot[i].push_back(room[i - j][j]);
            room_rot[i].push_back(0);
        }

        room_rot[i].pop_back();
        int padding = n + m - room_rot[i].size() - 1;
        for (int k = 0; k < padding; k++)
        {
            room_rot[i].push_back(0);
        }
    }
    /* rotate the room (bottom side) */
    for (int i = 1; i < m; i++)
    {
        /* add the offset */
        for (int k = 0; k < i; k++)
        {
            room_rot[i + n - 1].push_back(0);
        }

        for (int j = 0; j < m; j++)
        {
            if (i + j >= m || n - j - 1 < 0)
            {
                break;
            }
            room_rot[i + n - 1].push_back(room[n - j - 1][i + j]);
            room_rot[i + n - 1].push_back(0);
        }

        room_rot[i + n - 1].pop_back();

        int padding = n + m - room_rot[i + n - 1].size() - 1;
        for (int k = 0; k < padding; k++)
        {
            room_rot[i + n - 1].push_back(0);
        }
    }