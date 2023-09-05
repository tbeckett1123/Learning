using Calculator.Core.Contracts;

public interface ICalculatorWebHookSubscriptionService
{
    ISubscriptionRequest Subscribe(ISubscriptionRequest subscriptionRequest);
}