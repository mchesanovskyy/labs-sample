using System;

namespace MessageSendersInChain.Senders
{
    public class ValidateMessageLength : MessageSenderBase
    {
        public ValidateMessageLength() { }

        public override void Send(string message)
        {
            if (message.Length > 100)
            {
                throw new Exception("Message should be less than 100 chars");
            }

            Console.WriteLine($"[Message valid according to {nameof(ValidateNullMessage)} rule]");
            base.Send(message);
        }
    }
}