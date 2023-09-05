using MediatR;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;

namespace CalculatorWebHookSubscriptionManager.Api.Calculator
{
    public class CalculatorController : ApiController
    {
        private IMediator _Mediator;
        public CalculatorController(IMediator mediator) => _Mediator = mediator ?? throw new ArgumentNullException("mediator");
    }
}
