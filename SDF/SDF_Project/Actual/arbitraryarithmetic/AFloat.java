package arbitraryarithmetic;

public class AFloat extends AInteger{
    private String float_str;

    public AFloat(){
        this.float_str = "0.0";
    }
    public AFloat(String str_float){
        this.float_str = new String(str_float);
    }
    public AFloat(AFloat other_float){
        this.float_str = new String(other_float.float_str);
    }

    // to return the final result of the arithmetic operations
    public String return_string(){
        return this.float_str;
    }

    public static AFloat parse(String str_float){
        return new AFloat(str_float);
    }

    // -1 -> float1 is greater, 0 -> both are equal, 1-> float2 is greater.


    // a method to assist the 'sub' method
    private String sub_helper_float(String float_1, String float_2){
        String float1 = new String(float_1);
        String float2 = new String(float_2);
        
        // positive - negative
        if(float1.charAt(0)!='-' && float2.charAt(0)=='-'){
            return add_helper_float(float1, float2.substring(1));
        }
        // negative - positive
        else if(float1.charAt(0)=='-' && float2.charAt(0)!='-'){
            return add_helper_float(float1, '-' + float2);
        }

        // storing the indices of the decimal points
        int decimal1 = float1.indexOf('.');
        int decimal2 = float2.indexOf('.');

        // number of digits after the decimal
        int numAfterDecimal1 = float1.length()-decimal1-1;
        int numAfterDecimal2 = float2.length()-decimal2-1;
        // a variable to store the maximum of the above two variables
        int dec;

        // making the number of digits after the decimal equal
        if(numAfterDecimal1>numAfterDecimal2){ 
            float2 = float2 + "0".repeat(numAfterDecimal1 - numAfterDecimal2);
            dec = numAfterDecimal1;
        }
        else {
            float1 = float1 + "0".repeat(numAfterDecimal2 - numAfterDecimal1);
            dec = numAfterDecimal2;
        }

        // removing the decimal in the floats
        String f1 = float1.replace(String.valueOf('.'), "");
        String f2 = float2.replace(String.valueOf('.'), "");

        AInteger num1 = new AInteger(f1);
        AInteger num2 = new AInteger(f2);
        // subtracting the two ints without the decimal
        AInteger result = num1.sub(num2);

        // the final string, but without a decimal
        String resultStr = result.return_string();
        // storing the sign of the final string
        boolean is_negative = resultStr.startsWith("-");

        if(is_negative) resultStr = resultStr.substring(1);

        // padding the final string with zeroes to make the number of digits equal to the max
        // this is done for proper alignment of the digits for digit-wise subtraction when decimals are removed
        while(resultStr.length() <= dec){
            resultStr = "0" + resultStr;
        }

        // index at which the decimal should be placed
        int to_put_dec = resultStr.length() - dec;
        // inserting the decimal point
        StringBuilder final1 = new StringBuilder(resultStr).insert(to_put_dec, '.');
        
        // appending the proper sign
        if(is_negative) return final1.insert(0, '-').toString();
        return final1.toString();
    }

    private String add_helper_float(String float_1, String float_2){
        String float1 = new String(float_1);
        String float2 = new String(float_2);
        boolean result_is_negative = false;

        // negative + positive
        if(float1.charAt(0)=='-' && float2.charAt(0)!='-'){
            return sub_helper_float(float1, '-' + float2);
        }
        // positive + negative
        else if(float1.charAt(0)!='-' && float2.charAt(0)=='-'){
            return sub_helper_float(float1, float2.substring(1));
        }

        // storing the position of the decimal
        int decimal1 = float1.indexOf('.');
        int decimal2 = float2.indexOf('.');
        // a variable to store the maximum of the above two
        int dec;

        int numAfterDecimal1 = float1.length()-decimal1-1;
        int numAfterDecimal2 = float2.length()-decimal2-1;
        
        // making digits after the decimal equal
        if(numAfterDecimal1>numAfterDecimal2) {
            float2 = float2 + "0".repeat(numAfterDecimal1 - numAfterDecimal2);
            dec = numAfterDecimal1;
        }
        else {
            float1 = float1 + "0".repeat(numAfterDecimal2 - numAfterDecimal1);
            dec = numAfterDecimal2;
        }

        // removing the decimals, to use AInteger methods
        String f1 = float1.replace(String.valueOf('.'), "");
        String f2 = float2.replace(String.valueOf('.'), "");

        AInteger num1 = new AInteger(f1);
        AInteger num2 = new AInteger(f2);
        
        // adding the two floats, without the decimal
        AInteger result = num1.add(num2);
        // final result without the decimal
        String resultStr = result.return_string();

        // storing the sign of the result
        if(resultStr.startsWith("-")) {
            resultStr = resultStr.substring(1);
            result_is_negative = true;
        }
        else {
            result_is_negative = false;
        }
        
        // padding the result with zeroes
        while(resultStr.length() <= dec){
            resultStr = "0" + resultStr;
        }

        // index at which the decimal should be placed
        int to_put_dec = resultStr.length() - dec;
        // inserting the decimal back
        StringBuilder final1 = new StringBuilder(resultStr).insert(to_put_dec, '.');

        // assigning the proper sign
        if(result_is_negative) return final1.insert(0, '-').toString();
        else return final1.toString();
        
    }
    
    public AFloat add(AFloat other_float){
        if (!this.float_str.contains(".")) {
            this.float_str = this.float_str + ".0";
        }
        if (!other_float.float_str.contains(".")) {
            other_float.float_str = other_float.float_str + ".0";
        }
        String added_string = add_helper_float(this.float_str, other_float.float_str);
        AFloat result_afloat = new AFloat(added_string);
        return result_afloat;
    }

    public AFloat sub(AFloat other_float){
        if (!this.float_str.contains(".")) {
            this.float_str = this.float_str + ".0";
        }
        if (!other_float.float_str.contains(".")) {
            other_float.float_str = other_float.float_str + ".0";
        }
        String subbed_string = sub_helper_float(this.float_str, other_float.float_str);
        AFloat result_afloat = new AFloat(subbed_string);
        return result_afloat;
    }

    private String mul_helper_float(String float_1, String float_2){
        String float1 = new String(float_1);
        String float2 = new String(float_2);

        boolean result_is_positive = true;

        // positive * negative
        if(float1.charAt(0)!='-' && float2.charAt(0)=='-'){
            float2 = float2.substring(1);
            result_is_positive = false;
        }
        // negative * positive
        else if(float1.charAt(0)=='-' && float2.charAt(0)!='-'){
            float1 = float1.substring(1);
            result_is_positive = false;
        }
        // negative * negative
        else if(float1.charAt(0)=='-' && float2.charAt(0)=='-'){
            float1 = float1.substring(1);
            float2 = float2.substring(1);
        }

        // number of digits after the decimal
        int num_after_dec1 = float1.length() - float1.indexOf('.') - 1;
        int num_after_dec2 = float2.length() - float2.indexOf('.') - 1;
        // number of digits after which the decimal should be kept
        int dec = num_after_dec1 + num_after_dec2;
        
        // multiplying the two float, without the decimals
        String mulled_null_dec = mul_helper_int(float1.replace(".",""), float2.replace(".",""));
        mulled_null_dec = remove_leading_zeros(mulled_null_dec);
        
        // index at which the decimal should be placed
        int to_put_dec = mulled_null_dec.length() - dec;

        String mulled;

        // padding the result before placing the decimal
        if(to_put_dec<=0){
            mulled = "0." + "0".repeat(Math.abs(to_put_dec)) + mulled_null_dec;
        }
        // inserting the decimal at the proper index
        else{
            mulled = mulled_null_dec.substring(0, to_put_dec) + "." + mulled_null_dec.substring(to_put_dec);
        }

        if(result_is_positive) return mulled;
        return '-' + mulled;
    }


    public AFloat mul(AFloat other_float){
        if (!this.float_str.contains(".")) {
            this.float_str = this.float_str + ".0";
        }
        if (!other_float.float_str.contains(".")) {
            other_float.float_str = other_float.float_str + ".0";
        }
        String mulled_string = mul_helper_float(this.float_str, other_float.float_str);
        AFloat result_afloat = new AFloat(mulled_string);
        return result_afloat;
    }

    private String div_helper_float(String float_1, String float_2){
        String float1 = new String(float_1);
        String float2 = new String(float_2);
        boolean result_is_positive = true;

        // adding the decimal if not present
        if (float1.indexOf(".")==-1) {
            float1 = float1 + ".0";
        }
        if(float2.indexOf(".")==-1){
            float2 = float2 + ".0";
        }

        // negative / negative
        if(float1.charAt(0)=='-' && float2.charAt(0) == '-'){
            float1 = float1.substring(1);
            float2 = float2.substring(1);
        }
        // positive / negative
        else if(float1.charAt(0)!='-' && float2.charAt(0) == '-'){
            float2 = float2.substring(1);
            result_is_positive = false;
        }
        // negative / positive
        else if(float1.charAt(0)=='-' && float2.charAt(0) != '-'){
            float1 = float1.substring(1);
            result_is_positive = false;
        }

        int num_after_dec1 = float1.length() - float1.indexOf('.') - 1;
        int num_after_dec2 = float2.length() - float2.indexOf('.') - 1;
        int temp_dec_put = num_after_dec1 - num_after_dec2;

        // taking out the decimal point
        float1 = float1.replace(".","");
        float2 = float2.replace(".","");
        
        // handling the division by zero case
        if(remove_leading_zeros(float2) == "0"){
            return "Division by zero";
        }

        int precision = 30;

        float1 = remove_leading_zeros(float1);
        float2 = remove_leading_zeros(float2);

        String mul_temp = mul_helper_int("1"+"0".repeat(precision), float2);


        while(int_mod_compare(float1, mul_temp)==1){
            float1 += '0';
            temp_dec_put++;
        }
        // dividing the floats without a decimal
        String divved_int_dec_null = div_helper_int(float1, float2);

        // index at which the decimal should be placed
        int to_put_dec = divved_int_dec_null.length() - temp_dec_put;

        String divved;

        // padding the result before adding the decimal
        if(to_put_dec<=0){
            divved = "0." + "0".repeat(Math.abs(to_put_dec)) + divved_int_dec_null;
        }
        // inserting the decimal point at the proper index
        else{
            divved = divved_int_dec_null.substring(0, to_put_dec) + "." + divved_int_dec_null.substring(to_put_dec);
        }

        // assigning the proper sign 
        if(result_is_positive) return divved;
        return '-' + divved;
    }

    public AFloat div(AFloat other_float){
        if (!this.float_str.contains(".")) {
            this.float_str = this.float_str + ".0";
        }
        if (!other_float.float_str.contains(".")) {
            other_float.float_str = other_float.float_str + ".0";
        }
        String divved_string = div_helper_float(this.float_str, other_float.float_str);
        AFloat res_afloat = new AFloat(divved_string);
        return res_afloat;
    }

}