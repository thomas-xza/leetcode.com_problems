import java.awt.Point;
import java.util.ArrayList;

//  Very unfinished, just brushing up on Java.
//  Needs A-Star search implementing - see CS notes for the psuedocode and an explicit example.

class Solution {
    public int minMoves(String[] matrix) {

        int y_len = matrix.length;
        int x_len = matrix[0].length();

        System.out.println(x_len);
        System.out.println(y_len);

        for (String s : matrix) {

            System.out.println(s);

            System.out.println(matrix.length);

        }

        int[][] vs_prim = rebuild_datastructure(matrix);

        Map<Point, int[]> es = build_edges(vs_prim, y_len, x_len);

        int res = run_astar(es, vs_prim);

        System.out.println(es);

        return 0;

    }


    int run_astar(Map<Point, int[]> es, int[][] vs_prim) {

        queue

    }

    
    Map<Point, int[]> build_edges(int[][] vs, int y_len, int x_len) {

        Map<Point, int[]> es = new HashMap<>();

        List<Point> vs_obj = new ArrayList<>();

        int x, y;

        for (y = 0; y < y_len; y++) {

            for (x = 0; x < x_len ; x++) {

                Point key = new Point(x, y);
                vs_obj.add(key);

                int[] v = new int[4];
                v[0] = -64;

                System.out.println("hello");

                System.out.println(vs[y][x]);
                System.out.println(v[0]);

                if (y > 0 && x > 0 && x < x_len - 1 && y < y_len - 1){
                    int[] vv = {vs[y-1][x], vs[y][x-1], vs[y+1][x], vs[y][x+1]};
                    System.arraycopy(vv, 0, v, 0, 4);
                } else if (y == 0 && x > 0 && x < x_len - 1 && y < y_len - 1) {
                    int[] vv = {0, vs[y][x-1], vs[y+1][x], vs[y][x+1]};
                    System.arraycopy(vv, 0, v, 0, 4);
                } else if (y > 0 && x == 0 && x < x_len - 1 && y < y_len - 1) {
                    int[] vv = {vs[y-1][x], 0, vs[y+1][x], vs[y][x+1]};
                    System.arraycopy(vv, 0, v, 0, 4);
                } else if (y > 0 && x > 0 && x < x_len - 1 && y == y_len - 1) {
                    int[] vv = {vs[y-1][x], vs[y][x-1], 0, vs[y][x+1]};
                    System.arraycopy(vv, 0, v, 0, 4);
                } else if (y > 0 && x > 0 && x == x_len - 1 && y < y_len - 1) {
                    int[] vv = {vs[y-1][x], vs[y][x-1], vs[y+1][x], 0};
                    System.arraycopy(vv, 0, v, 0, 4);
                } else if (y == 0 && x == 0) {
                    int[] vv = {0, 0, vs[y+1][x], vs[y][x+1]};
                    System.arraycopy(vv, 0, v, 0, 4);
                } else if ( x == x_len - 1 && y == y_len - 1) {
                    int[] vv = {vs[y-1][x], vs[y][x-1], 0, 0};
                    System.arraycopy(vv, 0, v, 0, 4);
                }

                if (v[0] != -64) {
                    es.put(key, v);
                }
                
            }

        }

        return es;

    }

    int[][] rebuild_datastructure(String[] matrix) {

        // Need to find all edges first.

        int x;

        int y;

        int[][] v = new int[matrix.length][matrix[0].length()];

        for (y = 0; y < matrix.length; y++) {
            for (x = 0; x < matrix[y].length() ; x++) {

                char matrix_char = matrix[y].charAt(x);

                if (matrix_char == '#') {
                    v[y][x] = -1;

                } else if (matrix_char == '.') {
                    v[y][x] = 1;

                } else {
                    v[y][x] = (int)matrix_char;

                }

                System.out.println(v[y][x]);

            }

        }

        String[] a = {"test", "2"};

        return v;

    }



}
