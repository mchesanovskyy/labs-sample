namespace MessageSendersInChain
{
    public abstract class MessageSenderBase : IMessageSender
    {
        private IMessageSender _nextSender;

        protected MessageSenderBase()
        {
        }

        public void SetNext(MessageSenderBase nextSender)
        {
            _nextSender = nextSender;
        }

        public virtual void Send(string message)
        {
            if (_nextSender != null)
            {
                _nextSender.Send(message);
            }
        }
    }
}