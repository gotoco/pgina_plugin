using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.IO.Ports;

using pGina.Shared.Types;

using log4net;
using System.Threading;

namespace pGina.Plugin.HelloPlugin
{
    

    public class PluginImpl : pGina.Shared.Interfaces.IPluginAuthentication
    {
        static private SerialPort MyPort = new SerialPort("COM11");
        static Boolean _continue = true;
        static Boolean _authentication = false;

        private static ILog m_logger;

        private static readonly Guid m_uuid = new Guid("CED8D126-9121-4CD2-86DE-3D84E4A2625E");

        public PluginImpl()
        {
            m_logger = LogManager.GetLogger("pGina.Plugin.HelloPlugin");
        }

        public string Name
        {
            get { return "Hello"; }
        }

        public string Description
        {
            get { return "Authenticates users with 'hello' in the username and 'pGina' in the password"; }
        }

        public Guid Uuid
        {
            get { return m_uuid; }
        }

        public string Version
        {
            get
            {
                return System.Reflection.Assembly.GetExecutingAssembly().GetName().Version.ToString();
            }
        }

        public void Starting() { }

        public void Stopping() { }

        public BooleanResult AuthenticateUser(SessionProperties properties)
        {

            waitForData();

            UserInformation userInfo = properties.GetTrackedSingle<UserInformation>();
            try
            {

                if ((userInfo.Username.Contains("uBirds_ARM") && userInfo.Password.Contains("pGina")) || _authentication)
                {
                    // Successful authentication
                    m_logger.InfoFormat("Successfully authenticated {0}", userInfo.Username);
                    return new BooleanResult() { Success = true };
                }
                // Authentication failure
                m_logger.ErrorFormat("Authentication failed for {0}", userInfo.Username);
            }
            catch (Exception ex)
            {
                m_logger.InfoFormat("Exception throwed");
            }

            return new BooleanResult() { Success = false, Message = "Incorrect username or password." };
        }

        private static void OpenMyPort()
        {
            m_logger.InfoFormat("Trying to open port");

            try
            {
                MyPort.Open();
                m_logger.InfoFormat("port Successfully opened");
            }
            catch (Exception ex)
            {
                m_logger.InfoFormat("Error opening my port: {0}", ex.Message);
            }
        }

        public static void waitForData()
        {
            {
                string name;
                string message;
                StringComparer stringComparer = StringComparer.OrdinalIgnoreCase;
                Thread readThread = new Thread(Read);

                // Create a new SerialPort object with default settings.
                MyPort = new SerialPort("COM11");

                // Allow the user to set the appropriate properties.
                MyPort.BaudRate = 115200;

                // Set the read/write timeouts
                MyPort.ReadTimeout = 1000;
                MyPort.WriteTimeout = 1000;

                OpenMyPort();
                _continue = true;
                m_logger.InfoFormat("Type QUIT to exit");
                MyPort.WriteLine("Type QUIT to login");
                Read();




                //readThread.Join();
                MyPort.Close();
            }
        }

        public static void Read()
        {
            StringComparer stringComparer = StringComparer.OrdinalIgnoreCase;
            int i = 0;
            m_logger.InfoFormat("Read task ran..");
            MyPort.WriteLine("start");
            while (_continue && i<10000)
            {
                try
                {
                    string message = MyPort.ReadLine();
                    m_logger.InfoFormat(message);

                    m_logger.InfoFormat("compare = " + stringComparer.Equals("quit", message));
                    if (stringComparer.Equals("quit", message))
                    {
                        m_logger.InfoFormat("QUIT leaving..");
                        _authentication = true;
                        _continue = false;
                    }
                }
                catch (TimeoutException) { }
                m_logger.InfoFormat("i=" + i);
                i++;
            }
        }

    }
}
