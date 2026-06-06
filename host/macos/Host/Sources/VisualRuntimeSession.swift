import QuartzCore
import SwiftUI

@Observable
public final class VisualRuntimeSession {
    var backgroundColor: Color = .black {
        didSet {
            let resolved = backgroundColor.resolve(in: EnvironmentValues())
            host.setBackgroundColor(resolved.red, resolved.green, resolved.blue)
        }
    }
    @ObservationIgnored private var host: VisualRuntimeHost
    public var backendName: String {
        String(host.backendName())
    }

    public init?(libPath: String) {
        let host = VisualRuntimeHost(std.string(libPath))
        guard host.valid() else {
            return nil
        }
        self.host = host
    }

    func attach(_ layer: CAMetalLayer) {
        let size = layer.drawableSize
        host.attachSurface(
            Unmanaged.passUnretained(layer).toOpaque(),
            UInt32(size.width),
            UInt32(size.height)
        )
    }

    func resize(width: UInt32, height: UInt32) {
        host.resize(width, height)
    }
    
    func setBackgroundColor(r: Float, g: Float, b: Float) {
        host.setBackgroundColor(r, g, b)
    }
    
    func pan(dx: Float, dy: Float) {
        host.pan(dx, dy)
    }
    
    func zoom(delta: Float) {
        host.zoom(delta)
    }
    
    func addRectangle() {
        host.addRectangle();
    }

    func tick(_ dt: Float) {
        host.tick(dt)
    }

    func reload() {
        _ = host.reload()
    }
}
