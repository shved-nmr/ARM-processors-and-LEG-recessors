void bresenham(int x1, int y1, int x2, int y2) {
    bool isSteep = true;

    if (x2-x1 >= y2-y1){
        isSteep = false;
    } else {
        isSteep = true;
    }
    if (!isSteep) {
        int m_slope = 2 * (y2 - y1);
        int slope_error = m_slope - (x2 - x1);


        for (int x = x1, y = y1; x <= x2; x++) {

            slope_error += m_slope;

            if (slope_error >= 0) {
                y++;
                slope_error -= 2 * (x2 - x1);
            }
        }
    } else{
        int m_slope = 2 * (x2-x1);
        int slope_error = m_slope - (y2-y1);


        for (int y = y1, x = x1; y <= y2; y++) {
            // Add slope to increment angle formed
            slope_error += m_slope;

            // Slope error reached limit, time to
            // increment y and update slope error.
            if (slope_error >= 0)
            {
                x++;
                slope_error  -= 2 * (y2 - y1);
            }
        }
    }
}
