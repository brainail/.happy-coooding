using System;
using System.Text;
using System.Net;
using System.ComponentModel;

namespace WebClientDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                string pathToFile = "http://46.4.15.147:8080/Video/Full004/03675.ALEKSEI-Watch.Out.amvnews.ru.mp4";
            
                string pathToComputer = "data.mp4";
                WebClient webClient = new WebClient();
                WebProxy proxy = new WebProxy("proxy.bsu", 3128);
                proxy.Credentials = new NetworkCredential("fpm.malyshevEV", "skipskip");
                webClient.Proxy = proxy;
                webClient.DownloadFileCompleted += new AsyncCompletedEventHandler(webClient_DownloadFileCompleted);
                webClient.DownloadProgressChanged += new DownloadProgressChangedEventHandler(webClient_DownloadProgressChanged);
                webClient.DownloadFileAsync(new Uri(pathToFile), @pathToComputer);
                Console.ReadKey();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Could not download file: " + ex.Message);
            }
        }

        static void webClient_DownloadProgressChanged(object sender, DownloadProgressChangedEventArgs e)
        {
            Console.WriteLine(String.Format("{0} of {1} bytes downloaded ({2}% done)", e.BytesReceived, e.TotalBytesToReceive, e.ProgressPercentage));
        }

        static void webClient_DownloadFileCompleted(object sender, AsyncCompletedEventArgs e)
        {
            if (e.Error == null)
                Console.WriteLine("All done downloading the file!");
            else
                Console.WriteLine("Could not download file: " + e.Error.Message);
        }
    }
}