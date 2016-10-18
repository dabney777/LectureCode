/**
 * Created by Dabney on 10/16/2016.
 */
class Bucket {
    int[] key = new int[10];
    int quantity=0;
    public boolean insert(int _key){
        if (quantity<10){
            key[quantity++]=_key;
            return true;
        }else{return false;}
    }
    public boolean search(int _key){
        for(int i =0;i<quantity;i++){
            if(key[i]==_key) return true;
        }
        return false;
    }

    Bucket(int _key){
        key[0]=_key;
    }
    Bucket(){}

    public static void main(){


    }
}