using System;

namespace MessageSendersInChain.Senders
{
    public class ValidateNullMessage : MessageSenderBase
    {
        public ValidateNullMessage() { }

        public override void Send(string message)
        {
            if (message == null)
            {
                throw new Exception("Message is required");
            }

            Console.WriteLine($"[Message valid according to {nameof(ValidateNullMessage)} rule]");
            base.Send(message);
        }
    }
}