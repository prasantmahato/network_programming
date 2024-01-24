import java.util.Scanner;

public class demo {

    static final int INF = Integer.MAX_VALUE;

    static int[][][] dp;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();

        for (int t = 0; t < T; t++) {
            int N = scanner.nextInt();
            int M = scanner.nextInt();
            int K = scanner.nextInt();

            dp = new int[N + 1][M + 1][16];

            for (int i = 0; i <= N; i++) {
                for (int j = 0; j <= M; j++) {
                    for (int flag = 0; flag < 16; flag++) {
                        dp[i][j][flag] = INF;
                    }
                }
            }

            dp[0][0][0] = 0;

            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= M; j++) {
                    for (int flag = 0; flag < 16; flag++) {
                        dp[i][j][flag] = sq(i * j - K);

                        if ((flag & 1) != 0 || (flag & 2) != 0) {
                            for (int x = 1; x < i; x++) {
                                int u = dp[x][j][flag & ~8];
                                int v = dp[i - x][j][flag];
                                dp[i][j][flag] = Math.min(dp[i][j][flag], u + v);
                            }
                        }

                        if ((flag & 4) != 0 || (flag & 8) != 0) {
                            for (int y = 1; y < j; y++) {
                                int u = dp[i][y][flag & ~2];
                                int v = dp[i][j - y][flag & ~1];
                                dp[i][j][flag] = Math.min(dp[i][j][flag], u + v);
                            }
                        }
                    }
                }
            }

            int minCost = INF;
            for (int flag = 0; flag < 16; flag++) {
                minCost = Math.min(minCost, dp[N][M][flag]);
            }

            System.out.println(minCost);
        }
    }

    static int sq(int x) {
        return x * x;
    }
}