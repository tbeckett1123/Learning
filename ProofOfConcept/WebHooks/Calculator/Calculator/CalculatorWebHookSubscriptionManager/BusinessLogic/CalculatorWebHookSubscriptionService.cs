using Calculator.Core.Contracts;
using Calculator.DataService.Contracts;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace CalculatorWebHookSubscriptionManager.BusinessLogic
{
    public class CalculatorWebHookSubscriptionService : ICalculatorWebHookSubscriptionService
    {
        private readonly IDataService _DataService;
        public CalculatorWebHookSubscriptionService(IDataService dataService) => _DataService = dataService ?? throw new NullReferenceException("dataService");
        public ISubscriptionRequest Subscribe(ISubscriptionRequest subscriptionRequest)
        {
            subscriptionRequest.Token = Guid.NewGuid();

            return _DataService.PutSubscription(subscriptionRequest);
        }
    }
}