
public class Main {
 public static void main(String[] args) throws IOException
    {
      int a, b;
      StreamTokenizer in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));

    PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));

    while (in.nextToken() != StreamTokenizer.TT_EOF)
    // in.nextToken()读下一个标记，StreamTokenizer.TT_EOF是个参数EOF
        {
                a = (int) in.nval;
                in.nextToken();
                b = (int) in.nval;
                out.println(a + b);
        }
        out.flush();// 刷新缓冲区，否则a+b会留在缓冲区
        }