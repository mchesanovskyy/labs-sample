using System;

namespace MessageSendersInChain.Senders
{
    public class EmailMessageSender : MessageSenderBase
    {
        public EmailMessageSender() { }

        public override void Send(string message)
        {
            Console.WriteLine($"Send Email with {message}");
            base.Send(message);
        }
    }
}