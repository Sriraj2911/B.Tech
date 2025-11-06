import arbitraryarithmetic.AInteger;
import arbitraryarithmetic.AFloat;

public class MyInfArith{
    public static void main(String[] args){
        if(args.length!=4){
            System.out.println("Incorrect usage.");
            System.out.println("Usage: java MyInfArith.java <int/float> <add/sub/mul/div> num1 num2");
            System.exit(1);
        }
        if(args[0].equals("int")){
                AInteger num1 = new AInteger(args[2]);
                AInteger num2 = new AInteger(args[3]);
            if(args[1].equals("add")){
                AInteger result = num1.add(num2);
                System.out.println(result.return_string());
            }
            else if(args[1].equals("sub")){
                AInteger result = num1.sub(num2);
                System.out.println(result.return_string());
            }
            else if(args[1].equals("mul")){
                AInteger result = num1.mul(num2);
                System.out.println(result.return_string());
            }
            else if(args[1].equals("div")){
                AInteger result = num1.div(num2);
                System.out.println(result.return_string());
            }
            else{
                System.out.println("Incorrect usage.");
                System.out.println("Usage: java MyInfArith.java <int/float> <add/sub/mul/div> num1 num2");
                System.exit(1);
            }
        }
        else if(args[0].equals("float")){
            AFloat num1 = new AFloat(args[2]);
            AFloat num2 = new AFloat(args[3]);
            if(args[1].equals("add")){
                AFloat result = num1.add(num2);
                System.out.println(result.return_string());
            }
            else if(args[1].equals("sub")){
                AFloat result = num1.sub(num2);
                System.out.println(result.return_string());
            }
            else if(args[1].equals("mul")){
                AFloat result = num1.mul(num2);
                System.out.println(result.return_string());
            }
            else if(args[1].equals("div")){
                AFloat result = num1.div(num2);
                System.out.println(result.return_string());
            }
            else{
                System.out.println("Incorrect usage.");
                System.out.println("Usage: java MyInfArith.java <int/float> <add/sub/mul/div> num1 num2");
                System.exit(1);
            }
        }
        else{
            System.out.println("Incorrect usage.");
            System.out.println("Usage: java MyInfArith.java <int/float> <add/sub/mul/div> num1 num2");
            System.exit(1);
        }
    }
}