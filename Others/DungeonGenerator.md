```java
package generators;

import java.util.concurrent.ThreadLocalRandom;

public class DungeonGenerator {

    private int width;
    private int height;

    private char[][] web;

    private int x;
    private int y;

    public DungeonGenerator(int height, int width) {
        this.width = width;
        this.height = height;
        y = height/2;
        x = 0;

        web = new char[height][width];
        for(int i = 0; i < height; i++)
            for(int j = 0; j < width; j++)
                web[i][j] = ' ';
    }

    private int getRandomLength() {
        return ThreadLocalRandom.current().nextInt(3, 8);
    }

    private boolean isDirectionPossible(int dir, int len) {
        switch(dir) {
            case 0:
                return y - len >= 0;
            case 1:
                return  x + len < width;
            case 2:
                return y + len < height;
            case 3:
                return x - len >= 0;
            default:
                return false;
        }
    }

    private int getRandomDirection(int len) {
        int dir;
        do {
            dir = ThreadLocalRandom.current().nextInt(0, 4);
        } while (!isDirectionPossible(dir, len));
        return dir;
    }

    private void fill(int dir, int len) {
        for(int i = 0; i < len; i++) {
            web[y][x] = '*';
            switch(dir) {
                case 0:
                    y--;
                    break;
                case 1:
                    x++;
                    break;
                case 2:
                    y++;
                    break;
                case 3:
                    x--;
                    break;
            }
        }
    }

    private void generate() {
        for(int i = 0; i < 150; i++) {
            int len = getRandomLength();
            int dir = getRandomDirection(len);
            fill(dir,len);
        }
    }

    public void print() {
        generate();
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++)
                System.out.print(web[i][j]);
            System.out.println();
        }

    }

    public char[][] getWeb() {
        return web;
    }

    public static void main(String[] args) {
        new DungeonGenerator(30,100).print();
    }
}
```
