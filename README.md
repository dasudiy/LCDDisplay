# LCDDisplay

可以将串口输出显示在1602LCD的简单程序。

* \r0\r 清屏
* \r1\r 打开背光
* \r2\r 关闭背光

示例
```csharp
void Main()
{
	PerformanceCounter cpuCounter;
	PerformanceCounter ramCounter;

	cpuCounter = new PerformanceCounter("Processor", "% Processor Time", "_Total");
	ramCounter = new PerformanceCounter("Memory", "Available MBytes");

	var port = new System.IO.Ports.SerialPort("COM6", 115200);
	port.Open();
	using (var writer = new StreamWriter(port.BaseStream))
	{
		writer.Write("\r0\r");
		writer.Flush();
		while (true)
		{
			writer.Write("\r0\r");
			writer.Write($"CPU:{cpuCounter.NextValue().To<int>()}%\nMEM:{ramCounter.NextValue().To<int>()}MB\n");			
			writer.Flush();
			Thread.Sleep(1000);
		}
		port.Close();

	}
}

// You can define other methods, fields, classes and namespaces here
```
![demo.jpg](/demo.jpg)
