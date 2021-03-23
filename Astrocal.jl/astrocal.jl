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


t1=currentTime()
printTime(t1)
