struct Timespec
    sec::Int;
    nsec::Int
end

astroCalLib="/Users/dsc/git/CScratch/AstroCal/build/AstroCal/libAstroCal"

function currentTime()::Timespec
    ts=ccall((:ASTC_currentTimeUTC, astroCalLib),Timespec, ())
    return ts
end

function printTime(ts::Timespec)
    ccall((:ASTC_printTime, astroCalLib), Cvoid ,(Timespec,), ts)
end

function degreeToDecimal(d,m,s)::Float64
    ccall((:ASTC_degreeToDecimal, astroCalLib), Float64, (Int, Int, Float64), d, m, s)
end

function decimalToDegree(d)::(Int, Int, Float64)
    dd::Int=0
    m::Int=0
    s::Float64=0.0
    ccall((:ASTC_decimalToDegree, astroCalLib), Cvoid, (Float64, Ptr{Int}, Ptr{Int}, Ptr{Float64}), d, [dd], [m], [s])
    return (dd,m,s)
end

t1=currentTime()
printTime(t1)

println(degreeToDecimal(15,30,0.0))
println("test")
println(decimalToDegree(15.5e0))

