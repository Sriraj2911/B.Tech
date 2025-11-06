package arbitraryarithmetic;

public class AInteger{
    private String int_str;

    public AInteger(){
        this.int_str = "0";
    }
    public AInteger(String str_int){
        this.int_str = new String(str_int);
    }
    public AInteger(AInteger other_int){
        this.int_str = other_int.int_str;
    }

    // to return the final string
    public String return_string(){
        return this.int_str;
    }
    public static AInteger parse(String str_int){
        return new AInteger(str_int);
    }

    // -1 -> s1, 0 -> =, 1 -> s2
    protected int int_mod_compare(String s1, String s2){
        s1 = remove_leading_zeros(s1);
        s2 = remove_leading_zeros(s2);
        if(s1.length()>s2.length()){
            return -1;
        }
        else if(s2.length()>s1.length()){
            return 1;
        }
        else{
            if(s1.compareTo(s2)>0) return -1;
            else if(s1.compareTo(s2)==0) return 0;
            else return 1;
        }
    }

    // a helping method to assist the 'sub' method
    protected String sub_helper_int(String int_1, String int_2){
        String int1 = new String(int_1);
        String int2 = new String(int_2);

        // negative - positive -> negative + negative 
        if(int1.charAt(0)=='-' && int2.charAt(0)!='-'){
            return add_helper_int(int1, '-' + int2);
        }
        // positive - negative -> positive + positive
        else if(int1.charAt(0)!='-' && int2.charAt(0)=='-'){
            return add_helper_int(int_1, int_2.substring(1));
        }

        // boolean which stores whether the final answer is positive or negative
        boolean sign_fnl_pos = true;
        String  int_max;
        String int_min;

        // negative - negative
        if(int1.charAt(0)=='-' && int2.charAt(0)=='-'){
            if(int_mod_compare(int1, int2)==-1){
                sign_fnl_pos = false;
                // Taking the absolute values
                int_max = int1.substring(1);
                int_min = int2.substring(1);
            }
            else if(int_mod_compare(int1, int2)==0){
                return "0";
            }
            else{
                int_max = int2.substring(1);
                int_min = int1.substring(1);
            }
        }
        // positive - positive
        else{
            if(int_mod_compare(int1, int2)==-1){
                int_max = int1;
                int_min = int2;
            }
            else if(int_mod_compare(int1, int2)==0){
                return "0";
            }
            else{
                sign_fnl_pos = false;
                int_max = int2;
                int_min = int1;
            }
        }


        boolean carry = false;
        // int_max.length and int_min.length both give the number of digits, coz they are absolute values
        int max_digits = Math.max(int_max.length(), int_min.length());
        // string in which the final absolute value is stored (the sign is added at the end)
        String subbed_mod = "";

        for(int i=0;i<max_digits;i++){
            int digit_1 = (int_max.length()-1-i>=0) ? int_max.charAt(int_max.length() - i - 1) - '0' : 0;
            int digit_2 = (int_min.length()-1-i>=0) ? int_min.charAt(int_min.length() - i - 1) - '0' : 0;
            // the digit which is being subtracted
            int subbed = digit_1 - digit_2;

            // if carried from, then -1
            if(carry) subbed -= 1;

            // in n1 - n2, if n1 < n2
            if(subbed<0){
                subbed += 10;
                // we have to carry
                carry = true;
            }
            else carry = false;

            // concatenating the digit in question with the remaining number
            subbed_mod = subbed + subbed_mod;
        }

        if(sign_fnl_pos) return subbed_mod;
        else return '-' + subbed_mod;
    }

    // a helping method to assist the 'add' method
    protected String add_helper_int(String int_1, String int_2){
        boolean sign_fnl_pos = true;
        String int1 = new String(int_1);
        String int2 = new String(int_2);
        // negative + negative
        if(int1.charAt(0)=='-'&&int2.charAt(0)=='-'){
            sign_fnl_pos = false;
            // taking the absolute values
            int1 = int1.substring(1);
            int2 = int2.substring(1);
        }
        // negative + postive
        else if(int1.charAt(0)=='-' && int2.charAt(0)!='-'){
            return sub_helper_int(int2, int1.substring(1));
        }
        // positive + negative
        else if(int1.charAt(0)!='-' && int2.charAt(0)=='-'){
            return sub_helper_int(int1, int2.substring(1));
        }

        int max_digits = Math.max(int1.length(), int2.length());
        int carry = 0;
        // the string in which the final absolute value is stored (the sign is assigned later)
        String add_mod = "";

        for(int i=0;i<max_digits;i++){
            int digit_1 = (int1.length()-1-i>=0) ? int1.charAt(int1.length() - i - 1) - '0' : 0;
            int digit_2 = (int2.length()-1-i>=0) ? int2.charAt(int2.length() - i - 1) - '0' : 0;

            int added = digit_1 + digit_2 + carry;
            
            // this is concatenation, not addition
            add_mod = added % 10 + add_mod;
            carry = added / 10;
        }
        if(carry>0) add_mod = carry + add_mod;

        if(sign_fnl_pos) return add_mod;
        else return '-' + add_mod;

    }


    public AInteger add(AInteger other_int){
        return new AInteger(add_helper_int(this.int_str, other_int.int_str));
    }


    public AInteger sub(AInteger other_int){
        return new AInteger(sub_helper_int(this.int_str, other_int.int_str));
    }

    // a helping method to assist the 'mul' method
    protected String mul_helper_int(String int_1, String int_2){
        String int1 = new String(int_1);
        String int2 = new String(int_2);
        // boolean to store the final sign
        boolean sign_fnl_pos = true;

        // negative * negative
        if(int1.charAt(0)=='-' && int2.charAt(0)=='-'){
            int1 = int1.substring(1);
            int2 = int2.substring(1);
        }
        // negative * positive
        else if(int1.charAt(0)=='-' && int2.charAt(0)!='-'){
            sign_fnl_pos = false;
            int1 = int1.substring(1);
        }
        // positive * negative
        else if(int1.charAt(0)!='-' && int2.charAt(0)=='-'){
            sign_fnl_pos = false;
            int2 = int2.substring(1);
        }

        String mul_mod = "0";
        
        for(int i=0; i<int2.length();i++){
            int digit_1 = int2.charAt(int2.length() - 1 - i) - '0';
            String mul_help_mod = "0".repeat(i) + "";
            int carry = 0;
            
            for(int j=0; j<int1.length(); j++){
                int digit_2 = int1.charAt(int1.length() - 1 -j) - '0';
                int mulled = digit_1 * digit_2 + carry;

                mul_help_mod = mulled % 10 + mul_help_mod;
                carry = mulled / 10;
            }
            // concatenating the final carry to the start of the string
            if(carry>0) mul_help_mod = carry + mul_help_mod;

            mul_mod = add_helper_int(mul_mod, mul_help_mod);
        }

        if(sign_fnl_pos) return mul_mod;
        else return '-' + mul_mod;
    }

    protected String remove_leading_zeros(String s){
        for(int i=0;i<s.length();i++){
            if(s.charAt(i)!='0'){
                return s.substring(i);
            }
        }
        return "0";
    }

    // a helping method to assist the 'div' method
    protected String div_helper_int(String int_1, String int_2){
        String int1 = new String(int_1);
        String int2 = new String(int_2);

        
        // boolean to store the final sign
        boolean sign_fnl_pos = true;
        
        // removing leading zeroes to make things easier (like the following 'if' statement)
        int1 = remove_leading_zeros(int1);
        int2 = remove_leading_zeros(int2);
        
        if(int_2.equals("0")){
            System.out.println("Division by zero error");
            System.exit(1);
        }

        // directly returning "0" based on the string length (only possible coz the leading zeroes are removed)
        if(int_mod_compare(int1, int2)==1){
            return "0";
        }
        else if(int_mod_compare(int1, int2)==0){
            return "1";
        }

        // negative / positive
        if(int1.charAt(0)=='-' && int2.charAt(0)!='-'){
            sign_fnl_pos = false;
            int1 = int1.substring(1);
        }
        // positive / negative
        else if(int1.charAt(0)!='-' && int2.charAt(0)=='-'){
            sign_fnl_pos = false;
            int2 = int2.substring(1);
        }
        // negative / negative
        else if(int1.charAt(0)=='-' && int2.charAt(0)=='-'){
            int1 = int1.substring(1);
            int2 = int2.substring(1);
        }

        // stores the final answer
        String quotient_string = "";
        int to_take;
        // the part of int1 that is being divided by int2
        String dividing_string = int1.substring(0,int2.length());
        to_take = int2.length();
        
        // if the part considered before is less than int2, then add another digit to dividing_string
        if(int_mod_compare(dividing_string, int2)==1){
            dividing_string = int1.substring(0, int2.length()+1);
            to_take++;
        }

        while(true){
            // the part obtained from dividing_string/int2, which is to be added to the quotient
            String to_add_quotient = "1";


            // repeatedly dividing with multiples of int2 to get 'dividing_string//int2'
            while(int_mod_compare(dividing_string, mul_helper_int(to_add_quotient, int2))<=0){
                to_add_quotient = add_helper_int("1", to_add_quotient);
            }

            // since 'to_add_quotient' started from 1, 1 is being subtracted again
            to_add_quotient = sub_helper_int(to_add_quotient, "1");
            to_add_quotient = remove_leading_zeros(to_add_quotient);

            // concatenating to the final answer
            quotient_string += to_add_quotient;
            
            // checking if some part of int1 is remaining (if not, then the division is finished)
            if(to_take==int1.length()){
                if(sign_fnl_pos) return quotient_string;
                else return '-' + quotient_string;
            } 

            // if the part considered before is less than int2, then add another digit to dividing_string
            if(to_add_quotient.equals("0")){
                dividing_string = dividing_string + int1.charAt(to_take);
                to_take++;
                continue;
            }

            String remainder_string = sub_helper_int(dividing_string, mul_helper_int(to_add_quotient, int2));
            remainder_string = remove_leading_zeros(remainder_string);

            // concatenating the remainder to the following digit and repeating the process
            // the loop breaks when to_take==int1.length, as there would be nothing else to divide in int1
            dividing_string = remainder_string + int1.charAt(to_take);
            to_take++;
        }
    }


    public AInteger mul(AInteger other_int){
        return new AInteger(mul_helper_int(this.int_str, other_int.int_str));
    }

    public AInteger div(AInteger other_int){
        return new AInteger(div_helper_int(this.int_str, other_int.int_str));
    }
}