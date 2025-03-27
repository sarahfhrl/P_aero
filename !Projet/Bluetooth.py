import asyncio
import threading
from bleak import BleakClient
import tkinter as tk

DEVICE_ADDRESS = "0C:EB:7C:D1:DC:95"
COMMAND_CHARACTERISTIC_UUID = "00002A58-0000-1000-8000-00805f9b34fb"

class ArduinoApp:
    def __init__(self, root, loop):
        self.root = root
        self.loop = loop
        self.client = BleakClient(DEVICE_ADDRESS)
        self.is_connected = False
        self.acquisition_running = False

        # Interface utilisateur
        self.root.title("Contrôle Arduino")
        self.start_button = tk.Button(root, text="Démarrer l'acquisition", command=self.start_acquisition, state=tk.DISABLED)
        self.start_button.pack(pady=10)
        self.stop_button = tk.Button(root, text="Arrêter l'acquisition", command=self.stop_acquisition, state=tk.DISABLED)
        self.stop_button.pack(pady=10)

        self.status_label = tk.Label(root, text="Statut : Connexion en cours...")
        self.status_label.pack(pady=10)

        self.root.protocol("WM_DELETE_WINDOW", self.close_app)

        # Connexion Bluetooth
        asyncio.run_coroutine_threadsafe(self.connect(), self.loop)

    async def connect(self):
        await self.client.connect()
        self.is_connected = self.client.is_connected
        if self.is_connected:
            self.update_status("Statut : Connecté")
            self.update_buttons()
        else:
            self.update_status("Statut : Échec de connexion")
            self.disable_buttons()

    async def disconnect(self):
        if self.is_connected:
            await self.client.disconnect()
            self.is_connected = False
            self.acquisition_running = False
            self.update_status("Statut : Déconnecté")
            self.disable_buttons()

    async def send_command(self, command):
        if self.is_connected:
            await self.client.write_gatt_char(COMMAND_CHARACTERISTIC_UUID, bytearray([command]))

    def start_acquisition(self):
        if self.is_connected:
            asyncio.run_coroutine_threadsafe(self.send_command(1), self.loop)
            self.acquisition_running = True
            self.update_status("Acquisition en cours...")
            self.update_buttons()

    def stop_acquisition(self):
        if self.is_connected:
            asyncio.run_coroutine_threadsafe(self.send_command(0), self.loop)
            self.acquisition_running = False
            self.update_status("Acquisition arrêtée")
            self.update_buttons()

    def update_buttons(self):
        def _update():
            if self.is_connected:
                self.start_button.config(state=tk.NORMAL)
                self.stop_button.config(state=tk.NORMAL)
            else:
                self.start_button.config(state=tk.DISABLED)
                self.stop_button.config(state=tk.DISABLED)
        self.root.after(0, _update)

    def disable_buttons(self):
        self.root.after(0, lambda: [
            self.start_button.config(state=tk.DISABLED),
            self.stop_button.config(state=tk.DISABLED)
        ])

    def update_status(self, text):
        self.status_label.after(0, lambda: self.status_label.config(text=text))

    def close_app(self):
        if self.acquisition_running:
            self.stop_acquisition()
        asyncio.run_coroutine_threadsafe(self.disconnect(), self.loop)
        self.root.after(100, self.root.destroy)


def start_loop(loop):
    asyncio.set_event_loop(loop)
    loop.run_forever()


if __name__ == "__main__":
    loop = asyncio.new_event_loop()
    threading.Thread(target=start_loop, args=(loop,), daemon=True).start()

    root = tk.Tk()
    app = ArduinoApp(root, loop)
    root.mainloop()

    loop.call_soon_threadsafe(loop.stop)
