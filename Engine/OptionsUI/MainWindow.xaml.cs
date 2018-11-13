﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Launcher
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private const string fileName = "data/controllerSettings.dat";
        Process gameProcess = new Process();
        public enum ControllerKeyCodes
        {
            DPAD_UP = 0x0001,
            DPAD_DOWN = 0x0002,
            DPAD_LEFT = 0x0004,
            DPAD_RIGHT = 0x0008,
            START = 0x0010,
            BACK = 0x0020,
            LEFT_THUMB = 0x0040,
            RIGHT_THUMB = 0x0080,
            LEFT_SHOULDER = 0x0100,
            RIGHT_SHOULDER = 0x0200,
            A = 0x1000,
            B = 0x2000,
            X = 0x4000,
            Y = 0x8000,
        };
        public MainWindow()
        {
            InitializeComponent();
            List<ControllerKeyCodes> m_AllButtonsList =
                Enum.GetValues(typeof(ControllerKeyCodes)).Cast<ControllerKeyCodes>().ToList();

            cbxDUp.ItemsSource = m_AllButtonsList;
            cbxDUp.SelectedIndex = 0;
            cbxDDown.ItemsSource = m_AllButtonsList;
            cbxDDown.SelectedIndex = 1;
            cbxDLeft.ItemsSource = m_AllButtonsList;
            cbxDLeft.SelectedIndex = 2;
            cbxDRight.ItemsSource = m_AllButtonsList;
            cbxDRight.SelectedIndex = 3;
            cbxStart.ItemsSource = m_AllButtonsList;
            cbxStart.SelectedIndex = 4;
            cbxBack.ItemsSource = m_AllButtonsList;
            cbxBack.SelectedIndex = 5;
            cbxLTS.ItemsSource = m_AllButtonsList;
            cbxLTS.SelectedIndex = 6;
            cbxRTS.ItemsSource = m_AllButtonsList;
            cbxRTS.SelectedIndex = 7;
            cbxLB.ItemsSource = m_AllButtonsList;
            cbxLB.SelectedIndex = 8;
            cbxRB.ItemsSource = m_AllButtonsList;
            cbxRB.SelectedIndex = 9;
            cbxA.ItemsSource = m_AllButtonsList;
            cbxA.SelectedIndex = 10;
            cbxB.ItemsSource = m_AllButtonsList;
            cbxB.SelectedIndex = 11;
            cbxX.ItemsSource = m_AllButtonsList;
            cbxX.SelectedIndex = 12;
            cbxY.ItemsSource = m_AllButtonsList;
            cbxY.SelectedIndex = 13;
        }

        private void btnOkbutton_Click(object sender, RoutedEventArgs e)
        {
            using (BinaryWriter writer= new BinaryWriter(File.Open(fileName, FileMode.Create)))
            {
                writer.Write(Convert.ToInt32(Enum.Parse(typeof(ControllerKeyCodes), cbxDUp.SelectedItem.ToString())));
                writer.Write(Convert.ToInt32(Enum.Parse(typeof(ControllerKeyCodes), cbxDDown.SelectedItem.ToString())));
                writer.Write(Convert.ToInt32(Enum.Parse(typeof(ControllerKeyCodes), cbxDLeft.SelectedItem.ToString())));
                writer.Write(Convert.ToInt32(Enum.Parse(typeof(ControllerKeyCodes), cbxDRight.SelectedItem.ToString())));
                writer.Write(Convert.ToInt32(Enum.Parse(typeof(ControllerKeyCodes), cbxStart.SelectedItem.ToString())));
                writer.Write(Convert.ToInt32(Enum.Parse(typeof(ControllerKeyCodes), cbxBack.SelectedItem.ToString())));
                writer.Write(Convert.ToInt32(Enum.Parse(typeof(ControllerKeyCodes), cbxLTS.SelectedItem.ToString())));
                writer.Write(Convert.ToInt32(Enum.Parse(typeof(ControllerKeyCodes), cbxRTS.SelectedItem.ToString())));
                writer.Write(Convert.ToInt32(Enum.Parse(typeof(ControllerKeyCodes), cbxLB.SelectedItem.ToString())));
                writer.Write(Convert.ToInt32(Enum.Parse(typeof(ControllerKeyCodes), cbxRB.SelectedItem.ToString())));
                writer.Write(Convert.ToInt32(Enum.Parse(typeof(ControllerKeyCodes), cbxA.SelectedItem.ToString())));
                writer.Write(Convert.ToInt32(Enum.Parse(typeof(ControllerKeyCodes), cbxB.SelectedItem.ToString())));
                writer.Write(Convert.ToInt32(Enum.Parse(typeof(ControllerKeyCodes), cbxX.SelectedItem.ToString())));
                writer.Write(Convert.ToInt32(Enum.Parse(typeof(ControllerKeyCodes), cbxY.SelectedItem.ToString())));
            }

            gameProcess.StartInfo.FileName = "MyGame.exe";
            if (gameProcess.Start())
            {
                this.Close();
            }
            else
            {
                MessageBox.Show("Cannot Start game", "Error", MessageBoxButton.OK);
            }
        }

        private void btnCancelButton_Click(object sender, RoutedEventArgs e)
        {
            gameProcess.StartInfo.FileName = "MyGame.exe";
            if (gameProcess.Start())
            {
                this.Close();
            }
            else
            {
                MessageBox.Show("Cannot Start game", "Error", MessageBoxButton.OK);
            }
            this.Close();
        }
    }
}
