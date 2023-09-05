using Calculator.Core.Contracts;
using Calculator.DataService.Contracts;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculator.DataService.Models
{
    public class DataService : IDataService
    {
        public void DeleteCalculationRequest(Guid key)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<ICalculationRequest> GetCalculationRequests()
        {
            throw new NotImplementedException();
        }

        public IEnumerable<ISubscriptionRequest> GetSubscriptions()
        {
            throw new NotImplementedException();
        }

        public void PostCalculationRequest(ICalculationRequest request)
        {
            throw new NotImplementedException();
        }

        public ISubscriptionRequest PutSubscription(ISubscriptionRequest request)
        {
            throw new NotImplementedException();
        }
    }
}
