import java.io.*;

/**
 * Created by Dabney on 10/30/2016.
 */
public class LongestCommonSubsequents {
    String A;
    String B;
    public LongestCommonSubsequents(String _A, String _B){
        A=_A;
        B=_B;
        
    }
    private int max(int a ,int b){
        return a>b?a:b;
    }
    private  String findResult(int[][] Tracer,int i , int j){
        String s= new String();
        if(i==0||j==0) return s;
        if(Tracer[i][j]==1){

            return s+B.charAt(j-1)+findResult(Tracer,i-1,j-1);
        }else{
            if(Tracer[i][j]==2){
                return s+findResult(Tracer,i-1,j);
            }else{if(Tracer[i][j]==3){
                return s+findResult(Tracer,i,j-1);
                }else{
                    return s;
                }

            }

        }

    }

    public void findLCS(){
        char[] a= A.toCharArray();
        char[] b = B.toCharArray();
        int m=A.length()+1,n=B.length()+1;
        int[][] L = new int[m][n];
        int[][] Tracer = new int[m][n];
        for(int i =0;i<m;++i){L[0][i]=0;L[i][0]=0;}//initial matrix

        for(int i =1;i<m;++i){
            for(int j =1;j<n;++j) {
                if(a[i-1]==b[j-1]) {
                    L[i][j]=L[i-1][j-1]+1;
                    Tracer[i][j] = 1;//1 is top left,2 is top,3 is left
                }
                else{ if(L[i-1][j]>L[i][j-1])
                      {
                          L[i][j]=L[i-1][j];
                          Tracer[i][j]=2;
                      }
                        else{
                            L[i][j]=L[i][j-1];
                            Tracer[i][j]=3;
                            }
                    }
            }
            }
        String result = new String();
        StringBuffer re=new StringBuffer(findResult(Tracer,m-1,n-1));
        System.out.println("The longest common subsequents is : "+re.reverse());
        System.out.println("It's length is :"+re.length());
    }






    public static void main(String args[]){
        File file = new File("DATA.txt");
       try{
           BufferedReader reader =new BufferedReader( new InputStreamReader(new FileInputStream(file),"UTF-8" ));
           String A = reader.readLine();
           String B = reader.readLine();
           LongestCommonSubsequents LCS=new LongestCommonSubsequents(A,B);
           LCS.findLCS();
       }catch(Exception e){
           e.printStackTrace();
       }

    }
}
