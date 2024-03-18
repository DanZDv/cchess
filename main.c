#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void drawBoard(Display* d, Drawable w, GC gc, int tileSize) {
    int rows = 8;
    int cols = 8;
    
    XDrawRectangle(d, w, gc, 20, 20, (tileSize*cols), (tileSize*rows));
    for (int i = 0; i < cols; i++) {
      for (int j = 0; j < rows; j++) {
        if ((i + j) % 2 == 0) continue; //skip every other tile for checkered pattern
        // Calculate the x and y positions for the rectangle
          int x = 20 + (tileSize * i);
          int y = 20 + (tileSize * j);
          // Draw the rectangle
          XFillRectangle(d, w, gc, x, y, tileSize, tileSize);
      }
    }
}


int main() {
    Display *d;
    Window w;
    XEvent e;
    char *msg = "Hello, World!";
    int s;
    GC gc;

    d = XOpenDisplay(NULL);
    if (d == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 1920,1080, 1,
                            BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d, w);

    // Create a graphics context
    gc = XCreateGC(d, w, 0, NULL);
    XSetForeground(d, gc, BlackPixel(d, s)); // Set the foreground color


    while (1) {
        XNextEvent(d, &e);
        if (e.type == Expose) {
            
            // XDrawString(d, w, DefaultGC(d, s), 50, 50, msg, strlen(msg));
            drawBoard(d, w, gc, 150);
        }
        if (e.type == KeyPress) {
          break;
        }
    }

    XCloseDisplay(d);
    return 0;
}

