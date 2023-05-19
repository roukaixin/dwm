void
grid(Monitor *m) {
    int i, n, aw, ah;
    // client 的 x y轴，cw：宽，ch：高
    int cx, cy, cw, ch;
    // 行，列，最后一行多少个
    int rows, cols, lastRows;
    // 最后一行 x 坐标
    int lastX;
    Client *c;

    // 遍历窗口
    for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next)) {
        n++;
    }


    /* 网格的大小 */
    for (cols = 0; cols <= n / 2; cols++)
        if (cols * cols >= n)
            break;
    rows = (cols && (cols - 1) * cols >= n) ? cols - 1 : cols;

    /* window geoms (cell height/width) */
    ch = m->wh / (rows ? rows : 1);
    cw = m->ww / (cols ? cols : 1);

    // 计算最后一行多少个 client
    lastRows = n % cols;
    if (lastRows){
        lastX = (m->ww - lastRows * cw) / 2;
    }

    for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next)) {
        cx = m->wx + (i % cols) * cw;
        cy = m->wy + (i / cols) * ch;
        /* adjust height/width of last row/column's windows */
        ah = ((i + 1) % rows == 0) ? m->wh - ch * rows : 0;
        aw = (i >= rows * (cols - 1)) ? m->ww - cw * cols : 0;
        if ( lastRows && i >= n - lastRows){
            cx += lastX;
        }
        resize(c, cx, cy, cw - 2 * c->bw + aw, ch - 2 * c->bw + ah, False);
        i++;
    }
}