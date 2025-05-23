import Debug "mo:base/Debug";
import Float "mo:base/Float";
persistent actor Project{
// Decentralized Banking System
// CheckBalance, TopUp, WithDraw
// CheckBalance
stable var balance : Float = 100;
public func checkBalance(): async Text{
return "Your Balance is :" # Float.toText(balance);
};

// TopUp Function
public func topUp(amount : Float): async Text{
balance := balance + amount;
return "An amount :" # Float.toText(amount) # "added";
};

// WithDraw
public func withDraw(amount : Float): async Text{
balance := balance - amount;
return "An amount :" # Float.toText(amount) # "added";
 };
};
